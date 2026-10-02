// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ARoguePlayerCharacter::ARoguePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));
}

float ARoguePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ActionSystemComponent->ApplyHealthChange(-ActualDamage);

	return ActualDamage;
}

// Called to bind functionality to input
void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);

	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ThisClass::StartAction,  SharedGameplayTags::Action_Sprint.GetTag());
	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ThisClass::StopAction, SharedGameplayTags::Action_Sprint.GetTag());

	EnhancedInput->BindAction(Input_PrimaryAttack,	ETriggerEvent::Triggered, this, &ThisClass::StartAction, SharedGameplayTags::Action_PrimaryAttack.GetTag());
	EnhancedInput->BindAction(Input_SecondaryAttack,	ETriggerEvent::Triggered, this, &ThisClass::StartAction, SharedGameplayTags::Action_SecondaryAttack.GetTag());
	EnhancedInput->BindAction(Input_SpecialAttack,	ETriggerEvent::Triggered, this, &ThisClass::StartAction, SharedGameplayTags::Action_SpecialAttack.GetTag());
}

void ARoguePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
}

void ARoguePlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (NewHealth <= 0.0f || FMath::IsNearlyZero(NewHealth))
	{
		DisableInput(nullptr);

		GetMovementComponent()->StopMovementImmediately();

		PlayAnimMontage(DeathMontage);
	}
}

void ARoguePlayerCharacter::StartAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARoguePlayerCharacter::StopAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StopAction(InActionName);
}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	const auto InputValue = InValue.Get<FVector2D>();

	auto ControlRot = GetControlRotation();
	ControlRot.Pitch = .0f;

	//Forward/Backawrd
	AddMovementInput(ControlRot.Vector(), InputValue.X);

	// Sideways
	const auto RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARoguePlayerCharacter::Look(const FInputActionInstance& InValue)
{
	const auto InputValue = InValue.GetValue().Get<FVector2D>();
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

