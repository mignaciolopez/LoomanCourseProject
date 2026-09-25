// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectile.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ARogueProjectile::ARogueProjectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;
	SphereComp->SetSphereRadius(16.0f);
	SphereComp->SetCollisionProfileName(TEXT("Projectile"));

	LoopEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopEffectComp"));
	LoopEffectComp->SetupAttachment(SphereComp);

	LoopAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopAudioComp"));
	LoopAudioComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 2000.f;
	MovementComp->ProjectileGravityScale = 0.0f;
}

void ARogueProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	PlayEndEffects();

	Destroy();
}

void ARogueProjectile::PlayEndEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EndEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, EndSound, GetActorLocation(), FRotator::ZeroRotator);
}

void ARogueProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ARogueProjectile::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

