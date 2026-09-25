// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"


// Sets default values
URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplyHealthChange(const float DeltaValue)
{
	float OldHealth = Attributes.Health;

	float MaxHealth = GetDefault<URogueActionSystemComponent>()->Attributes.Health;

	Attributes.Health = FMath::Clamp(Attributes.Health + DeltaValue, 0.0f, MaxHealth);

	if (!FMath::IsNearlyEqual(Attributes.Health, OldHealth))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}

	UE_LOG(LogTemp, Log, TEXT("MaxHealth: %2f, Health: %2f"), MaxHealth, Attributes.Health);
}

