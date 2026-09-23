// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class ARogueProjectileMagic;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
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

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	TSubclassOf<ARogueProjectileMagic> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	FName MuzzleSocketName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);

	void PrimaryAttack(const FInputActionInstance& InputActionInstance);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
