// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RogueGameMode.h"
#include "RoguePrimaryGameMode.generated.h"

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

	void SpawnQueryCompleted(TSharedPtr<FEnvQueryResult> QueryResult);

	UPROPERTY(EditDefaultsOnly, Category="Spawn System")
	TObjectPtr<UEnvQuery> SpawnLocationQuery;
};
