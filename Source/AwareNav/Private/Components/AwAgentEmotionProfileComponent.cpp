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
