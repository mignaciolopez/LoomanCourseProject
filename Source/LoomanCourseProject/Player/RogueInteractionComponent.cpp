// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"


URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());

	if (PC)
	{
		if (PC->GetPawn())
		{
			const FVector Center = PC->GetPawn()->GetActorLocation();
			DrawDebugBox(GetWorld(), Center, FVector(20), FColor::Red);
		}
	}
}

