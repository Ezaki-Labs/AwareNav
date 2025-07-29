#include "Components/AwAgentEmotionProfileComponent.h"

#include "AwareNavSettings.h"
#include "Data/AwAgentEmotionGroupProfile.h"
#include "NavAreas/AwEmotionNavAreas.h"

UAwAgentEmotionProfileComponent::UAwAgentEmotionProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
			FEmotionNavAreaGroup EmotionNavAreaGroup = UAwEmotionNavArea_Base::GetNavAreaGroupByEmotionType(AreaMultiplier.Key);
			EmotionalAreaCostMultipliers.Add(EmotionNavAreaGroup.DefaultArea, AreaMultiplier.Value.DefaultCost);
			EmotionalAreaCostMultipliers.Add(EmotionNavAreaGroup.LowCostArea, AreaMultiplier.Value.LowCost);
			EmotionalAreaCostMultipliers.Add(EmotionNavAreaGroup.HighCostArea, AreaMultiplier.Value.HighCost);
		}
	}
	else
	{
		checkf(false, TEXT("Invalid Emotion GroupID"));
	}
}

void UAwAgentEmotionProfileComponent::BoostEmotion(const EAwEmotionType EmotionType, const float BoostMultiplier, const float BoostTime)
{
	if (BoostMultiplier <= 0.0f)
	{
		return;
	}
	
	const FEmotionNavAreaGroup EmotionNavAreaGroup = UAwEmotionNavArea_Base::GetNavAreaGroupByEmotionType(EmotionType);

	auto AlterEmotionNavAreaCost = [this](const TSubclassOf<UAwEmotionNavArea_Base>& NavArea, float Multiplier)
	{
		if (EmotionalAreaCostMultipliers.Contains(NavArea))
		{
			EmotionalAreaCostMultipliers[NavArea] *= Multiplier;
		}
		else
		{
			EmotionalAreaCostMultipliers.Add(NavArea, Multiplier);
		}
	};

	AlterEmotionNavAreaCost(EmotionNavAreaGroup.LowCostArea, BoostMultiplier);
	AlterEmotionNavAreaCost(EmotionNavAreaGroup.DefaultArea, BoostMultiplier);
	AlterEmotionNavAreaCost(EmotionNavAreaGroup.HighCostArea, BoostMultiplier);

	if (BoostTime > 0.0f)
	{
		TWeakObjectPtr<UAwAgentEmotionProfileComponent> WeakThis(this);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			FTimerDelegate::CreateLambda([WeakThis, EmotionNavAreaGroup, BoostMultiplier]()
			{
				if (!WeakThis.IsValid()) return;

				auto& MultiplierMap = WeakThis->EmotionalAreaCostMultipliers;

				auto RevertCost = [&](const TSubclassOf<UAwEmotionNavArea_Base>& NavArea)
				{
					if (MultiplierMap.Contains(NavArea))
					{
						MultiplierMap[NavArea] /= BoostMultiplier;
					}
				};

				RevertCost(EmotionNavAreaGroup.LowCostArea);
				RevertCost(EmotionNavAreaGroup.DefaultArea);
				RevertCost(EmotionNavAreaGroup.HighCostArea);
			}),
			BoostTime,
			false
		);
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
