// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueGameTypes.h"
#include "Core/RogueGameMode.h"
#include "RoguePrimaryGameMode.generated.h"

struct FMonsterSpawnData;
struct FEnvQueryResult;
class UEnvQuery;
/**
 * 
 */
UCLASS()
class LOOMANCOURSEPROJECT_API ARoguePrimaryGameMode : public ARogueGameMode
{
	GENERATED_BODY()

public:

	ARoguePrimaryGameMode();

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category= "Spawn System")
	TArray<FRogueDirectorData> Directors;

	bool TrySpawnMonster(FRogueDirectorData& Director);

	void SpawnQueryCompleted(TSharedPtr<FEnvQueryResult> QueryResult, FMonsterSpawnData* SelectedMonster);

	void OnMonsterClassLoaded(const FSoftObjectPath& LoadedObjectPath, UObject* LoadedObject, FVector SpawnLocation, FMonsterSpawnData* SelectedMonster);
};