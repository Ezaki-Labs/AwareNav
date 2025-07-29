#include "Components/AwAgentEmotionProfileComponent.h"

#include "AwareNavSettings.h"
#include "Data/AwAgentEmotionGroupProfile.h"
#include "NavAreas/AwEmotionNavAreas.h"

UAwAgentEmotionProfileComponent::UAwAgentEmotionProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAwAgentEmotionProfileComponent::SetAgentEmotionGroupProfile(const FName GroupID)
{
	if (GroupID.IsNone())
	{
		return;
	}

	if (const FAwAgentEmotionGroupProfile* PermissionGroupRow = EmotionGroupTable->FindRow<FAwAgentEmotionGroupProfile>(GroupID, TEXT("Emotion Group Lookup")))
	{
		for (auto AreaMultiplier: PermissionGroupRow->EmotionalAreaCostMultipliers)
		{
			FEmotionNavAreaGroup EmotionNavAreaGroup = UAwEmotionNavArea_Base::GetNavAreaByEmotionType(AreaMultiplier.Key);
			EmotionalAreaCostMultipliers.Add(EmotionNavAreaGroup.DefaultArea, AreaMultiplier.Value.DefaultCost);
			EmotionalAreaCostMultipliers.Add(EmotionNavAreaGroup.LowCostArea, AreaMultiplier.Value.LowCost);
			EmotionalAreaCostMultipliers.Add(EmotionNavAreaGroup.HighCostArea, AreaMultiplier.Value.HighCost);
		}
	}
}

void UAwAgentEmotionProfileComponent::EnterEmotionVolume(AAwEmotionAreaVolume* EmotionAreaVolume)
{
	if (IsValid(EmotionAreaVolume) && !AreasAgentIsIn.Contains(EmotionAreaVolume))
	{
		AreasAgentIsIn.Add(EmotionAreaVolume);
		OnEnteredEmotionVolume.Broadcast(EmotionAreaVolume);
	}
}

void UAwAgentEmotionProfileComponent::LeaveEmotionVolume(AAwEmotionAreaVolume* EmotionAreaVolume)
{
	if (IsValid(EmotionAreaVolume) && AreasAgentIsIn.Contains(EmotionAreaVolume))
	{
		AreasAgentIsIn.Remove(EmotionAreaVolume);
		OnLeftEmotionVolume.Broadcast(EmotionAreaVolume);
	}
}

void UAwAgentEmotionProfileComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
	if (Settings && Settings->EmotionGroupProfilesTable.IsValid())
	{
		EmotionGroupTable = Settings->EmotionGroupProfilesTable.LoadSynchronous();
		check(EmotionGroupTable);
	}

	SetAgentEmotionGroupProfile(EmotionGroupID);
}

void UAwAgentEmotionProfileComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AAwEmotionAreaVolume* EmotionAreaVolume: AreasAgentIsIn)
	{
		if (IsValid(EmotionAreaVolume))
		{
			EmotionAreaVolume->ForceLeaveArea(this);
			OnLeftEmotionVolume.Broadcast(EmotionAreaVolume);			
		}
	}
	
	Super::EndPlay(EndPlayReason);
}
