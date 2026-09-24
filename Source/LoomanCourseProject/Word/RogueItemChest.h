// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class LOOMANCOURSEPROJECT_API ARogueItemChest : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Comopnents")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Comopnents")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimationSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimationTargetPitch = 120.0f;

	float CurrentAnimationPitch = 0.0f;

	virtual void BeginPlay() override;

public:
	ARogueItemChest();

	virtual void Tick(float DeltaTime) override;


};
