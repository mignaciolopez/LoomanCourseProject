// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class LOOMANCOURSEPROJECT_API ARogueItemChest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueItemChest();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
