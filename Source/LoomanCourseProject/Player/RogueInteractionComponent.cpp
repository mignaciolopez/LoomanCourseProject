// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "RogueGameTypes.h"
#include "Engine/OverlapResult.h"
#include "Core/RogueInteractionInterface.h"


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
	FVector Center = PC->GetPawn()->GetActorLocation();
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	float HighestDot = -1.0f;
	SelectedActor = nullptr;

	for (FOverlapResult& Overlap : Overlaps)
	{
		if (Overlap.GetActor())
		{
			FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
			FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();

			const float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
			if (DotResult > HighestDot)
			{
				HighestDot = DotResult;
				SelectedActor = Overlap.GetActor();
			}

			DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
			FString DebugString = FString::Printf(TEXT("DOT: %2f"), DotResult);
			DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
		}
	}

	if (SelectedActor)
	{
		DrawDebugBox(GetWorld(), SelectedActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}

	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
}

void URogueInteractionComponent::Interact()
{
	if (const auto InteractInterface = Cast<IRogueInteractionInterface>(SelectedActor))
	{
		InteractInterface->Interact();
	}
}

