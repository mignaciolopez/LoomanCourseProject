// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;

UCLASS(Abstract)
class LOOMANCOURSEPROJECT_API ARogueProjectileMagic : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueProjectileMagic();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
