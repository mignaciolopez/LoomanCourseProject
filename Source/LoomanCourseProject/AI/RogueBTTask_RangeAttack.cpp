// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_RangeAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Projectiles/RogueProjectile.h"

EBTNodeResult::Type URogueBTTask_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Pawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	check(Pawn);

	AActor* NewProjectile = nullptr;
	if (Pawn)
	{
		const auto SpawnLocation = Pawn->GetMesh()->GetSocketLocation(MuzzleSocketName);

		const auto BBComp = OwnerComp.GetBlackboardComponent();
		const auto TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if (TargetActor)
		{
			const auto Direction = TargetActor->GetActorLocation() - SpawnLocation;
			auto SpawnRotation = Direction.Rotation();

			SpawnRotation.Pitch	+= FMath::RandRange(0.0f, MaxBulletSpread);
			SpawnRotation.Yaw	+= FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = Pawn;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}

	return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
