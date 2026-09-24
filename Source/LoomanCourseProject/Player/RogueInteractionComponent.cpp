// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "Engine/OverlapResult.h"


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

	ECollisionChannel CollisionChannel = ECC_Visibility;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);

	AActor* BestActor = nullptr;
	float HighestDot = -1.0f;

	for (FOverlapResult& Overlap : Overlaps)
	{
		if (Overlap.GetActor())
		{
			FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();

			DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);

			FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
			const float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());

			FString DebugString = FString::Printf(TEXT("DOT: %2f"), DotResult);
			DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);

			if (DotResult > HighestDot)
			{
				HighestDot = DotResult;
				BestActor = Overlap.GetActor();
			}
		}
	}

	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}
}

