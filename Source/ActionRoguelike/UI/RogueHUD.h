// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RogueHUD.generated.h"

class URogueMainHudWidget;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARogueHUD : public AHUD
{
	GENERATED_BODY()

public:

	URogueMainHudWidget* GetMainHUD() const
	{
		return MainWidgetInstance;
	}

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<URogueMainHudWidget> MainWidgetClass;

	UPROPERTY()
	TObjectPtr<URogueMainHudWidget> MainWidgetInstance;
};
