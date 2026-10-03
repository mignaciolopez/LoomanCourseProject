// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAttributeSet.h"

#include "RogueActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URogueActionSystemComponent* URogueAttributeSet::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}



// Health
URogueHealthAttributeSet::URogueHealthAttributeSet()
{
	Health = FRogueAttribute(100.0f);
	HealthMax = FRogueAttribute(Health.GetValue());
}

void URogueHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.0f, HealthMax.GetValue());
}



// Pawn
URoguePawnAttributeSet::URoguePawnAttributeSet()
{
	MoveSpeed = FRogueAttribute(550.0f);
	MoveSpeedMultiplier = FRogueAttribute(1.0f);
}

void URoguePawnAttributeSet::PostAttributeChanged()
{
	Super::PostAttributeChanged();

	ApplyMoveSpeed();
}

void URoguePawnAttributeSet::InitializeAttributes()
{
	Super::InitializeAttributes();

	ApplyMoveSpeed();
}

void URoguePawnAttributeSet::ApplyMoveSpeed()
{
	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningComponent()->GetOwner());
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed.GetValue() * MoveSpeedMultiplier.GetValue();
}



// Player
URoguePlayerAttributeSet::URoguePlayerAttributeSet()
{
	Rage = FRogueAttribute(30.0f);
}



// Mobs
URogueMonsterAttributeSet::URogueMonsterAttributeSet()
{
	MoveSpeed = FRogueAttribute(450.0f);
}
