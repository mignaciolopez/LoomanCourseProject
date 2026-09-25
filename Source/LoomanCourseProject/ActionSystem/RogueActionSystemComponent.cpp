// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"


// Sets default values
URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplyHealthChange(const float DeltaValue)
{
	float OldHealth = Attributes.Health;
	Attributes.Health += DeltaValue;
	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);

	UE_LOG(LogTemp, Log, TEXT("Health: %2f"), Attributes.Health);
}

