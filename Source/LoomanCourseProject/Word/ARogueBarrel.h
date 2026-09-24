// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "ARogueBarrel.generated.h"

class UDamageType;
class UNiagaraSystem;
class URadialForceComponent;
class USoundBase;
class UStaticMeshComponent;

UCLASS(Abstract)
class LOOMANCOURSEPROJECT_API ARogueBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogueBarrel();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	float ExplosionDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> DamagedEffect;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> DamagedSound;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DmgTypeClass;

	UFUNCTION(BlueprintCallable)
	void Explode();
	void DestroyAfterDelay();

	bool bIsDamaged = false;

	FTimerHandle ExplodeTimerHandle;

private:

	TObjectPtr<UNiagaraComponent> CurrentEffect = nullptr;
	TObjectPtr<UAudioComponent> CurrentSound = nullptr;
};
