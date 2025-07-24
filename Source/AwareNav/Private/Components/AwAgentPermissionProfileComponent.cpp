#include "Components/AwAgentPermissionProfileComponent.h"

#include "AwareNavSettings.h"
#include "Data/AwAgentPermissionGroupProfile.h"

UAwAgentPermissionProfileComponent::UAwAgentPermissionProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAwAgentPermissionProfileComponent::SetAgentPermissionGroupProfile(const FName GroupID)
{
	if (GroupID.IsNone())
	{
		return;
	}

	if (const FAwAgentPermissionGroupProfile* PermissionGroupRow = PermissionGroupTable->FindRow<FAwAgentPermissionGroupProfile>(GroupID, TEXT("Permission Group Lookup")))
	{
		PermissionLevels = PermissionGroupRow->PermissionLevels;
	}
}

void UAwAgentPermissionProfileComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
	if (Settings && Settings->PermissionGroupProfilesTable.IsValid())
	{
		PermissionGroupTable = Settings->PermissionGroupProfilesTable.LoadSynchronous();
		check(PermissionGroupTable);
	}

	SetAgentPermissionGroupProfile(PermissionGroupID);
}
