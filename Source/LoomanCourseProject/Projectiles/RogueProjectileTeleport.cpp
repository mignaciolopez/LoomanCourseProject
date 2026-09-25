// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"


ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	MovementComp->InitialSpeed = 6000.0f;
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::StartDelayedTeleport, DetonateDelay);
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TeleportHandle);

	StartDelayedTeleport();
}


void ARogueProjectileTeleport::StartDelayedTeleport()
{
	PlayEndEffects();

	MovementComp->StopMovementImmediately();

	if (LoopEffectComp)
		LoopEffectComp->Deactivate();

	if (LoopAudioComp)
		LoopAudioComp->Stop();

	SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::HandleTeleportation, TeleportSecondaryDelay);
}

void ARogueProjectileTeleport::HandleTeleportation()
{
	APawn* ActorToTeleport = GetInstigator();

	if (ActorToTeleport)
	{
		check(ActorToTeleport);
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	}

	Destroy();
}