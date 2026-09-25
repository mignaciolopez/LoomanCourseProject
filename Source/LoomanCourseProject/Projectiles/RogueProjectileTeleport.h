// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileTeleport.generated.h"

UCLASS(Abstract)
class LOOMANCOURSEPROJECT_API ARogueProjectileTeleport : public ARogueProjectile
{
	GENERATED_BODY()

protected:

	FTimerHandle TeleportHandle;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float DetonateDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float TeleportSecondaryDelay = 0.2f;

	void StartDelayedTeleport();

	void HandleTeleportation();

	virtual void BeginPlay() override;

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;

public:

	ARogueProjectileTeleport();
};