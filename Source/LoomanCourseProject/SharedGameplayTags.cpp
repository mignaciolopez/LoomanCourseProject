#include "SharedGameplayTags.h"

namespace SharedGameplayTags
{
	// Attributes
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Health, "Attribute.Health");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_HealthMax, "Attribute.HealthMax");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Rage, "Attribute.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Attribute_RageMax, "Attribute.RageMax");

	// Actions
	UE_DEFINE_GAMEPLAY_TAG(Action_Sprint, "Action.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(Action_PrimaryAttack, "Action.PrimaryAttack");
	UE_DEFINE_GAMEPLAY_TAG(Action_SecondaryAttack, "Action.SecondaryAttack");
	UE_DEFINE_GAMEPLAY_TAG(Action_SpecialAttack, "Action.SpecialAttack");
}