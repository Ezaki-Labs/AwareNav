#include "Components/AwAgentPermissionProfileComponent.h"

#include "AwareNavSettings.h"
#include "Data/AwAgentPermissionGroupProfile.h"

UAwAgentPermissionProfileComponent::UAwAgentPermissionProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

void UAwAgentPermissionProfileComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AAwRestrictedAreaVolume* EmotionAreaVolume: AreasAgentIsIn)
	{
		if (IsValid(EmotionAreaVolume))
		{
			EmotionAreaVolume->ForceLeaveArea(this);
			OnLeftRestrictedVolume.Broadcast(EmotionAreaVolume);			
		}
	}
	
	Super::EndPlay(EndPlayReason);
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
	else
	{
		checkf(false, TEXT("Invalid Permisssion GroupID"));
	}
}

void UAwAgentPermissionProfileComponent::EnterPermissionVolume(AAwRestrictedAreaVolume* RestrictedAreaVolume)
{
	if (IsValid(RestrictedAreaVolume) && !AreasAgentIsIn.Contains(RestrictedAreaVolume))
	{
		AreasAgentIsIn.Add(RestrictedAreaVolume);
		OnEnteredRestrictedVolume.Broadcast(RestrictedAreaVolume);
	}
}

void UAwAgentPermissionProfileComponent::LeavePermissionVolume(AAwRestrictedAreaVolume* RestrictedAreaVolume)
{
	if (IsValid(RestrictedAreaVolume) && AreasAgentIsIn.Contains(RestrictedAreaVolume))
	{
		AreasAgentIsIn.Remove(RestrictedAreaVolume);
		OnLeftRestrictedVolume.Broadcast(RestrictedAreaVolume);
	}
}
