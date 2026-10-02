// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "RogueActionSystemComponent.generated.h"

struct FRogueAttribute;
class URogueAttributeSet;
struct FGameplayTag;
class URogueAction;


UENUM()
enum EAttributeModifyType
{
	Invalid,
	Base,
	Modifier,
	OverrideBase
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOOMANCOURSEPROJECT_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URogueActionSystemComponent();

	virtual void InitializeComponent() override;

	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	void GrantAction(TSubclassOf<URogueAction> ActionClass);

	void ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifyType ModifyType);

	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag);



	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FGameplayTagContainer ActiveGameplayTags;

protected:

	UPROPERTY()
	TObjectPtr<URogueAttributeSet> Attributes;

	TMap<FGameplayTag, FRogueAttribute*> CachedAttributes;

	UPROPERTY(EditAnywhere, Category="Attributes", NoClear)
	TSubclassOf<URogueAttributeSet> AttributeSetClass;

	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;

};
