#include "API/AwAwarenessLibrary.h"

#include "Actors/AwRestrictedAreaVolume.h"
#include "Components/AwAgentEmotionProfileComponent.h"
#include "Components/AwAgentPermissionProfileComponent.h"

#pragma region Permissions
void UAwAwarenessLibrary::SetAgentPermissionGroupProfile(const AActor* Agent, const FName GroupID)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentPermissionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->SetAgentPermissionGroupProfile(GroupID);
	}
}

void UAwAwarenessLibrary::SetAreaPermission(AAwRestrictedAreaVolume* Area, const EAwPermissionLevel NewPermission)
{
	if (!Area)
	{
		return;
	}

	Area->SetPermissionLevel(NewPermission);
}
#pragma endregion

#pragma region Emotions
void UAwAwarenessLibrary::SetAgentEmotionGroupProfile(const AActor* Agent, const FName GroupID)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentEmotionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->SetAgentEmotionGroupProfile(GroupID);
	}
}
#pragma endregion
