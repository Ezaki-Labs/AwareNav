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

	if (const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>())
	{
		if (Settings->EmotionGroupProfilesTable.IsValid())
		{
			EmotionGroupTable = Settings->EmotionGroupProfilesTable.LoadSynchronous();
			check(EmotionGroupTable);
		}
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
		EmotionAreaCostMultipliers = PermissionGroupRow->EmotionalAreaCostMultipliers;
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
	
	if (EmotionAreaCostMultipliers.Contains(EmotionType))
	{
		EmotionAreaCostMultipliers[EmotionType] *= BoostMultiplier;
	}
	else
	{
		EmotionAreaCostMultipliers.Add(EmotionType, BoostMultiplier);
	}

	if (BoostTime > 0.0f)
	{
		TWeakObjectPtr<UAwAgentEmotionProfileComponent> WeakThis(this);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			FTimerDelegate::CreateLambda([WeakThis, EmotionType, BoostMultiplier]()
			{
				if (!WeakThis.IsValid())
				{
					return;
				}

				auto& MultiplierMap = WeakThis->EmotionAreaCostMultipliers;

				if (MultiplierMap.Contains(EmotionType))
				{
					MultiplierMap[EmotionType] /= BoostMultiplier;
				}
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
