// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RogueBTTask_RangeAttack.generated.h"

class ARogueProjectile;

/**
 * 
 */
UCLASS()
class LOOMANCOURSEPROJECT_API URogueBTTask_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URogueBTTask_RangeAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category="AI")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<ARogueProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="AI")
	float MaxBulletSpread = 5.0f;
};
