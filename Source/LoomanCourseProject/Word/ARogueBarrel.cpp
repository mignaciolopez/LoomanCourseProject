// Fill out your copyright notice in the Description page of Project Settings.


#include "ARogueBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARogueBarrel::ARogueBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName("PhysicsActor");
	RootComponent = MeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->ImpulseStrength = 200000.0f;
	RadialForceComponent->Radius = 500.0f;
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->bIgnoreOwningActor = true;
}

float ARogueBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	auto DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!bIsDamaged)
	{
		bIsDamaged = true;
		CurrentSound = UGameplayStatics::SpawnSoundAttached(DamagedSound, MeshComponent);

		CurrentEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(DamagedEffect, MeshComponent, NAME_None,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

		GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ARogueBarrel::Explode, ExplosionDelay, false);
	}

	return DamageTaken;
}

void ARogueBarrel::Explode()
{
	if (CurrentSound)
		CurrentSound->Stop();

	if (CurrentEffect)
		CurrentEffect->Deactivate();

	RadialForceComponent->FireImpulse();

	MeshComponent->AddImpulse(FVector::UpVector * 1000, NAME_None, true);
	MeshComponent->AddAngularImpulseInDegrees(FVector::RightVector * 1000, NAME_None, true);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);

	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ARogueBarrel::DestroyAfterDelay, 0.6f, false);
}

void ARogueBarrel::DestroyAfterDelay()
{
	Destroy();
}