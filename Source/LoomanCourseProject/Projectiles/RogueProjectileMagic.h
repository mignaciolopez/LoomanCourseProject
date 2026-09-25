// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

UCLASS(Abstract)
class LOOMANCOURSEPROJECT_API ARogueProjectileMagic : public ARogueProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueProjectileMagic();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void PostInitializeComponents() override;

};
