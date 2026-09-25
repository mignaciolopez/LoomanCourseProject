// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"


// Sets default values
URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplyHealthChange(const float DeltaValue)
{
	AttributeSet.Health += DeltaValue;

	UE_LOG(LogTemp, Log, TEXT("Health: %2f"), AttributeSet.Health);
}

