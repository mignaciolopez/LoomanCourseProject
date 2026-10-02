// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"

struct FGameplayTag;
struct FInputActionValue;
struct FInputActionInstance;
class UInputAction;
class URogueActionSystemComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LOOMANCOURSEPROJECT_API ARoguePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoguePlayerCharacter();

	virtual void PostInitializeComponents() override;

	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float OldHealth);

	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);

	UPROPERTY(VisibleAnywhere, Category="Comonents")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category="Comonents")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Comonents")
	TObjectPtr<URogueActionSystemComponent> ActionSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category="Death")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Sprint;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;

};
