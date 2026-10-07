// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "URogueEnvQeryContext_AlivePlayers.generated.h"

/**
 * 
 */
UCLASS()
class LOOMANCOURSEPROJECT_API UURogueEnvQeryContext_AlivePlayers : public UEnvQueryContext
{
	GENERATED_BODY()

public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

};
