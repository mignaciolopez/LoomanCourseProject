// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class ARogueProjectileMagic;
class UAnimMontage;
class UInputAction;
class UCameraComponent;
class UNiagaraSystem;
class USpringArmComponent;
class USoundBase;
struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class LOOMANCOURSEPROJECT_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogueCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Comonents")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category="Comonents")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TSubclassOf<ARogueProjectileMagic> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TObjectPtr<USoundBase> CastingSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);

	void PrimaryAttack(const FInputActionInstance& InputActionInstance);

	void AttackTimerElapsed();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
