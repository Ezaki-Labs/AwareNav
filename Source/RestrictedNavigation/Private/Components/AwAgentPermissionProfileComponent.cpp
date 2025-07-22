#include "Components/AwAgentPermissionProfileComponent.h"

#include "Data/AwAgentPermissionGroupProfile.h"

UAwAgentPermissionProfileComponent::UAwAgentPermissionProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAwAgentPermissionProfileComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!bUseIndividualPermissionProfile)
	{
		if (FAwAgentPermissionGroupProfile* NavigationPermissionsTemplate = PermissionGroupProfile.GetRow<FAwAgentPermissionGroupProfile>(TEXT("Getting Data")))
		{
			PermissionLevels = NavigationPermissionsTemplate->PermissionLevels;
		}		
	}
}
