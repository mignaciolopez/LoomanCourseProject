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

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void End();

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

};
