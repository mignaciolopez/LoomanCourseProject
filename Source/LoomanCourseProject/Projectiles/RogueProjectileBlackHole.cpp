// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBlackHole.h"

#include "RogueGameTypes.h"
#include "Components/SphereComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackHole::ARogueProjectileBlackHole()
{
	SphereComp->SetSphereRadius(16.0f);
	MovementComp->InitialSpeed = 2000.f;
	MovementComp->ProjectileGravityScale = 0.0f;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->ForceStrength = 200000.0f;
	RadialForceComponent->Radius = 500.0f;
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->bIgnoreOwningActor = true;
}

void ARogueProjectileBlackHole::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle EndTimerHandle;
	float DelayTime = 5.33f;
	GetWorldTimerManager().SetTimer(EndTimerHandle, this, &ARogueProjectileBlackHole::End, DelayTime);
}

void ARogueProjectileBlackHole::End()
{
	Destroy();
}

void ARogueProjectileBlackHole::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	RadialForceComponent->UpdateOverlaps();
}

