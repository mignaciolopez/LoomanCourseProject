// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UAudioComponent;
class USoundBase;

UCLASS(Abstract)
class LOOMANCOURSEPROJECT_API ARogueProjectile : public AActor
{
	GENERATED_BODY()

public:

	ARogueProjectile();

	virtual void PostInitializeComponents() override;

protected:

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void PlayEndEffects();

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	TObjectPtr<UProjectileMovementComponent> MovementComp;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraComponent> LoopEffectComp;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> EndEffect;

	UPROPERTY(EditDefaultsOnly, Category="Audio")
	TObjectPtr<UAudioComponent> LoopAudioComp;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> EndSound;

};
