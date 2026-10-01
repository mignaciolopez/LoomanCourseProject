// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction_ProjectileAttack.h"

#include "NiagaraFunctionLibrary.h"
#include "RogueGameTypes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/RogueProjectile.h"


URogueAction_ProjectileAttack::URogueAction_ProjectileAttack()
{
	MuzzleSocketName = FName("Muzzle_01");
}

void URogueAction_ProjectileAttack::StartAction_Implementation()
{
	Super::StartAction_Implementation();

	URogueActionSystemComponent* ActionComp = GetOwningComponent();
	if (!ActionComp)
	{
		return;
	}
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	if (!Character)
	{
		return;
	}

	Character->PlayAnimMontage(AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, Character->GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);

	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;

	// Passing in the projectile as the parameter
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::AttackTimerElapsed, AttackDelayTime, false);
}

void URogueAction_ProjectileAttack::AttackTimerElapsed()
{
	URogueActionSystemComponent* ActionComp = GetOwningComponent();
	if (!ActionComp)
	{
		return;
	}
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	if (!Character)
	{
		return;
	}

	UWorld* World = GetWorld();
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FHitResult Hit;
	FVector EyeLocation;
	FRotator EyeRotation;
	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);

	FVector TraceEnd = EyeLocation + EyeRotation.Vector() * 5000.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character);
	if (World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_PROJECTILE, QueryParams))
	{
		TraceEnd = Hit.Location;
	}

	FRotator SpawnRotation = (TraceEnd - SpawnLocation).Rotation();

	AActor* NewProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	Character->MoveIgnoreActorAdd(NewProjectile);

#if !UE_BUILD_SHIPPING // Not necessary as Debug draw is not shipped.
	const float DebugLifeTime = CVarProjectileAimDebugDraw.GetValueOnGameThread();
	if (DebugLifeTime > 0.0f)
	{
		//The Hit Location or Trace End
		DrawDebugBox(World, TraceEnd, FVector(20.0f), FColor::Green, false, DebugLifeTime);

		// Adjusted Line Trace
		DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, DebugLifeTime);

		//New Projectile Path
		DrawDebugLine(World, SpawnLocation, TraceEnd, FColor::Yellow, false, DebugLifeTime);

		//Original Path Projectile
		DrawDebugLine(World, SpawnLocation, SpawnLocation + EyeRotation.Vector() * 5000.0f,
			FColor::Purple, false, DebugLifeTime);
	}
#endif
}
