// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RoguePlayerController.generated.h"

class UInputAction;
class URogueInteractionComponent;
/**
 * 
 */
UCLASS()
class LOOMANCOURSEPROJECT_API ARoguePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Interact;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<URogueInteractionComponent> InteractionComponent;

	virtual void SetupInputComponent() override;

	void StartInteract();

public:

	ARoguePlayerController();
};
