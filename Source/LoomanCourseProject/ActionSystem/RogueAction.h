// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

/**
 * 
 */
UCLASS()
class LOOMANCOURSEPROJECT_API URogueAction : public UObject
{
	GENERATED_BODY()

public:

	void StartAction();
	FName GetActionName() const { return ActionName; }

protected:

	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName = FName("PrimaryAttack");

};
