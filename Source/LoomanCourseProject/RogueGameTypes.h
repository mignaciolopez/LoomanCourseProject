// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "RogueGameTypes.generated.h"

class ARogueAICharacter;
class UEnvQuery;
class UDataTable;

static TAutoConsoleVariable<float> CVarProjectileAimDebugDraw(TEXT("game.projectile.aim.DebugDraw"), 0.0f,
                                                              TEXT("Draws debug lines for Projectiles aiming. (0 = off, > 0 is duration)"), ECVF_Cheat);

#define NAME_TargetActor "TargetActor"

#define COLLISION_INTERACTION	ECC_GameTraceChannel1
#define COLLISION_ATTRACTION	ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2


USTRUCT(BlueprintType)
struct FMonsterSpawnData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ARogueAICharacter> MonsterClass;

	// Points Required by gamemode to spawn unit
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;
};


USTRUCT(BlueprintType)
struct FRogueDirectorData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Spawn System")
	TObjectPtr<UEnvQuery> SpawnLocationQuery;

	UPROPERTY(EditDefaultsOnly, Category="Spawn System")
	TObjectPtr<UDataTable> MonsterSpawnTable;

	UPROPERTY(EditDefaultsOnly, Category="Spawn System")
	FRuntimeFloatCurve CreditGainCurve;

	UPROPERTY(EditDefaultsOnly, Category="Spawn System")
	float TickInterval = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="Spawn System")
	float TimeBetweenWaves = 6.0f;

	float CurrentCredits = 0.0f;

	float NextTickTime = 0.0f;
};