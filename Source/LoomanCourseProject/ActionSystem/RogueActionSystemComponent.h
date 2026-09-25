// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueActionSystemComponent.generated.h"


struct FRogueAttributeSet
{
	FRogueAttributeSet()
		: Health(100.0f) {}

	float Health;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOOMANCOURSEPROJECT_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URogueActionSystemComponent();

	void ApplyHealthChange(float DeltaValue);

protected:

	FRogueAttributeSet AttributeSet;

};
