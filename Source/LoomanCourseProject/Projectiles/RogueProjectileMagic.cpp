// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARogueProjectileMagic::ARogueProjectileMagic()
{
	SphereComp->SetSphereRadius(16.0f);
	MovementComp->InitialSpeed = 2000.f;
	MovementComp->ProjectileGravityScale = 0.0f;

}

void ARogueProjectileMagic::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, GetActorRotation().Vector(), Hit,
		GetInstigatorController(), this, DmgTypeClass);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EndEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, EndSound, GetActorLocation());

	Destroy();
}

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.AddDynamic(this, &ARogueProjectileMagic::OnHit);
}

