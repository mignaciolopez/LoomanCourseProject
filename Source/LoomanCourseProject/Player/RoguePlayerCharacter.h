// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "Projectiles/RogueProjectile.h"
#include "RoguePlayerCharacter.generated.h"

class UAnimMontage;
class UInputAction;
class UCameraComponent;
class UNiagaraSystem;
class USpringArmComponent;
class USoundBase;
struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class LOOMANCOURSEPROJECT_API ARoguePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoguePlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category="Comonents")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category="Comonents")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;

	// Projectile Attack
	UPROPERTY(EditDefaultsOnly, Category="Primary Attack")
	TSubclassOf<ARogueProjectile> PrimaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Secondary Attack")
	TSubclassOf<ARogueProjectile> SecondaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Special Attack")
	TSubclassOf<ARogueProjectile> SpecialAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TSubclassOf<ARogueProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
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

	void StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass);
	void AttackTimerElapsed(TSubclassOf<ARogueProjectile> ProjectileClass);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
