// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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

	MuzzleSocketName = FName("Muzzle_01");
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

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);

	EnhancedInput->BindAction(Input_PrimaryAttack,	ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::StartProjectileAttack, PrimaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SecondaryAttack,	ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::StartProjectileAttack, SecondaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SpecialAttack,	ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::StartProjectileAttack, SpecialAttackProjectileClass);
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

void ARoguePlayerCharacter::StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass)
{
	PlayAnimMontage(AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);

	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;

	// Passing in the projectile as the parameter
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ARoguePlayerCharacter::AttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, false);
}

void ARoguePlayerCharacter::AttackTimerElapsed(TSubclassOf<ARogueProjectile> ProjectileClass)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	MoveIgnoreActorAdd(NewProjectile);
}

