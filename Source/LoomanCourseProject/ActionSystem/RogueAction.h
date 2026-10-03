// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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

	UFUNCTION(BlueprintNativeEvent, Category="Actions")
	void StartAction();

	UFUNCTION(BlueprintNativeEvent, Category="Actions")
	void StopAction();

	bool CanStart() const;

	bool IsRunning() const
	{
		return bIsRunning;
	}

	FGameplayTag GetActionName() const { return ActionName; }

	UFUNCTION(BlueprintCallable, Category="Actions")
	URogueActionSystemComponent* GetOwningComponent() const;

	float GetCooldownTimeRemaining() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FGameplayTag ActionName;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FGameplayTagContainer GrantedTags;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	float CooldownTime = 0.0f;

	UPROPERTY(Transient)
	float CooldownUntil = 0;

	UPROPERTY(Transient)
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TMap<FGameplayTag, float> ActivationCost;
};
