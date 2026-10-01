// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

class URogueActionSystemComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class LOOMANCOURSEPROJECT_API URogueAction : public UObject
{
	GENERATED_BODY()

public:

	virtual void StartAction();
	FName GetActionName() const { return ActionName; }


	URogueActionSystemComponent* GetOwningComponent() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName = FName("PrimaryAttack");

};
