// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBlackHole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackHole::ARogueProjectileBlackHole()
{
	SphereComp->SetSphereRadius(15.0f);
	SphereComp->SetCollisionProfileName("Blackhole");
	MovementComp->InitialSpeed = 500.f;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->ForceStrength = -800000.0f; //Negative to Pull In
	RadialForceComponent->Radius = 1200.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	InitialLifeSpan = 5.33f;
}

void ARogueProjectileBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Cubes in the World Must have GenerateOverlapEvents Enabled
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackHole::OnOverlap);
}

void ARogueProjectileBlackHole::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

