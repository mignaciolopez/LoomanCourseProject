// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHUD.h"

#include "RogueMainHudWidget.h"
#include "Blueprint/UserWidget.h"

void ARogueHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass)
	{
		MainWidgetInstance = CreateWidget<URogueMainHudWidget>(GetOwningPlayerController(), MainWidgetClass);
		MainWidgetInstance->AddToViewport();
	}
}
