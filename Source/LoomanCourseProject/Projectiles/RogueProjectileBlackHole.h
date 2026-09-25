// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileBlackHole.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class LOOMANCOURSEPROJECT_API ARogueProjectileBlackHole : public ARogueProjectile
{
	GENERATED_BODY()

public:

	ARogueProjectileBlackHole();

	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
