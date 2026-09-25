// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARogueProjectileMagic::ARogueProjectileMagic()
{
	MovementComp->InitialSpeed = 2000.f;
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, GetActorRotation().Vector(), Hit,
		GetInstigatorController(), this, DmgTypeClass);
}

