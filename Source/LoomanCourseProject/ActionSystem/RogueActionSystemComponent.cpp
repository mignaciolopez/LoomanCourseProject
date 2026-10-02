// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"

#include "RogueAction.h"
#include "RogueAttributeSet.h"


// Sets default values
URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;

	AttributeSetClass = URogueAttributeSet::StaticClass();
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Attributes = NewObject<URogueAttributeSet>(this, AttributeSetClass);

	for (TFieldIterator<FStructProperty> PropIt(Attributes.GetClass()); PropIt; ++PropIt)
	{
		FStructProperty* StructProp = *PropIt;

		FRogueAttribute* FoundAttribute = PropIt->ContainerPtrToValuePtr<FRogueAttribute>(Attributes);

		FName AttributeTagName = FName("Attribute." + PropIt->GetName());
		FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);

		CachedAttributes.Add(AttributeTag, FoundAttribute);
	}

	for (TSubclassOf<URogueAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
}

void URogueActionSystemComponent::StartAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Action not found: %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Action not found: %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::ApplyHealthChange(const float DeltaValue)
{
	/*float OldHealth = Attributes.Health;

	Attributes.Health = FMath::Clamp(Attributes.Health + DeltaValue, 0.0f, Attributes.HealthMax);

	if (!FMath::IsNearlyEqual(Attributes.Health, OldHealth))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}

	UE_LOG(LogTemp, Log, TEXT("New Health: %2f, Max Health: %2f"), Attributes.Health, Attributes.HealthMax);*/
}

bool URogueActionSystemComponent::IsFullHealth() const
{
	return true;//FMath::IsNearlyEqual(Attributes.HealthMax, Attributes.Health);
}

FRogueAttribute* URogueActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag)
{
	FRogueAttribute** FoundAttribute = CachedAttributes.Find(InAttributeTag);

	return *FoundAttribute;
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> ActionClass)
{
	URogueAction* NewAction = NewObject<URogueAction>(this, ActionClass);
	Actions.Add(NewAction);
}
