#pragma once
#include "NativeGameplayTags.h"

namespace SharedGameplayTags
{
	// Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Health)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_HealthMax)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Rage);

	// Actions
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_PrimaryAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_SecondaryAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_SpecialAttack);
}
