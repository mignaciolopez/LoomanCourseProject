// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOOMANCOURSEPROJECT_API URogueInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionRadius = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DistanceToWeightScale = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DirectionWeightScale = 1.0f;

	UPROPERTY()
	TObjectPtr<AActor> SelectedActor = nullptr;

public:
	// Sets default values for this component's properties
	URogueInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Interact();
};
