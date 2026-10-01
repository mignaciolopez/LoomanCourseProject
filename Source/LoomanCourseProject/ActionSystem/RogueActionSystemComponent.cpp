// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"

#include "RogueAction.h"


// Sets default values
URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	URogueAction* NewAction = NewObject<URogueAction>(this, URogueAction::StaticClass());
	Actions.Add(NewAction);
}

void URogueActionSystemComponent::StartAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StartAction();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Action not found: %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::ApplyHealthChange(const float DeltaValue)
{
	float OldHealth = Attributes.Health;

	Attributes.Health = FMath::Clamp(Attributes.Health + DeltaValue, 0.0f, Attributes.HealthMax);

	if (!FMath::IsNearlyEqual(Attributes.Health, OldHealth))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}

	UE_LOG(LogTemp, Log, TEXT("New Health: %2f, Max Health: %2f"), Attributes.Health, Attributes.HealthMax);
}

bool URogueActionSystemComponent::IsFullHealth() const
{
	return FMath::IsNearlyEqual(Attributes.HealthMax, Attributes.Health);
}

float URogueActionSystemComponent::GetHealth() const
{
	return Attributes.Health;
}

float URogueActionSystemComponent::GetHealthMax() const
{
	return Attributes.HealthMax;
}