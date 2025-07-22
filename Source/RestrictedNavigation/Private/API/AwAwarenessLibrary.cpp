#include "API/AwAwarenessLibrary.h"

#include "Actors/AwRestrictedAreaVolume.h"
#include "Components/AwAgentPermissionProfileComponent.h"

void UAwAwarenessLibrary::SetAgentGroupProfile(const AActor* Agent, const FName GroupID)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentPermissionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->SetAgentGroupProfile(GroupID);
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
