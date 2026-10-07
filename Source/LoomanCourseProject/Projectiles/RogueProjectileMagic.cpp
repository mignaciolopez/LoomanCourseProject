// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "ActionSystem/RogueActionSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ActionSystem/RogueActionEffect.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ARogueProjectileMagic::ARogueProjectileMagic()
{
	MovementComp->InitialSpeed = 2000.f;

	InitialLifeSpan = 8.0f;
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, GetActorRotation().Vector(), Hit,
		GetInstigatorController(), this, DmgTypeClass);

	if (EffectOnHit)
	{
		URogueActionSystemComponent* ActionComp = OtherActor->FindComponentByClass<URogueActionSystemComponent>();
		if (ActionComp) // Not everything will have one
		{
			ActionComp->GrantAction(EffectOnHit);
		}
	}
}

