
#pragma once

static TAutoConsoleVariable<float> CVarProjectileAimDebugDraw(TEXT("game.projectile.aim.DebugDraw"), 0.0f,
	TEXT("Draws debug lines for Projectiles aiming. (0 = off, > 0 is duration)"), ECVF_Cheat);

#define NAME_TargetActor "TargetActor"

#define COLLISION_INTERACTION	ECC_GameTraceChannel1
#define COLLISION_ATTRACTION	ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2