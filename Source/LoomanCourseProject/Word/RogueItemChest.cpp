// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueItemChest.h"


// Sets default values
ARogueItemChest::ARogueItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

