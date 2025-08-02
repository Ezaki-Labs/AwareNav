#include "Components/AwAgentEmotionProfileComponent.h"

#include "AwareNavSettings.h"
#include "Actors/AwEmotionAreaVolume.h"
#include "Data/AwAgentEmotionalAbilityGroupProfile.h"
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

void UAwAgentEmotionProfileComponent::CalculateNavCosts()
{
	const float Courage = FMath::Clamp(AbilityGroup.Courage, 1, 20);

	float FearNavCost = 1.0f;
	if (Courage > 10)
	{
		// From 10 to 20 → 1.0 → 0.5
		const float CourageT = (Courage - 10) / 10.0f;
		FearNavCost = FMath::Lerp(1.0f, 0.5f, CourageT);
	}
	else if (Courage < 10)
	{
		// From 10 to 1 → 1.0 → 3.0
		const float CourageT = (10 - Courage) / 9.0f;
		FearNavCost = FMath::Lerp(1.0f, 3.0f, CourageT);
	}
	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Fear::StaticClass(), FearNavCost);


	const float ComfortSeeking = FMath::Clamp(AbilityGroup.ComfortSeeking, 1, 20);

	const float ComfortSeekingT = (ComfortSeeking - 1) / 19.0f; // Range: 0.0 to 1.0
	const float SafetyNavCost =  FMath::Lerp(1.0f, 0.3f, ComfortSeekingT);
	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Safety::StaticClass(), SafetyNavCost);

	
	const float Memory = FMath::Clamp(AbilityGroup.Memory, 1, 20);
	const float MemoryT = (Memory - 1) / 19.0f;
	
	const float HauntingNavCost = FMath::Lerp(1.0f, FearNavCost, MemoryT);	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Haunting::StaticClass(), HauntingNavCost);	
	
	const float NostalgiaNavCost = FMath::Lerp(1.0f, SafetyNavCost, MemoryT);	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Nostalgia::StaticClass(), NostalgiaNavCost);			
}

void UAwAgentEmotionProfileComponent::SetAgentEmotionGroupProfile(const FName GroupID)
{
	if (GroupID.IsNone())
	{
		return;
	}

	if (const FAwAgentEmotionalAbilityGroupProfile* PermissionGroupRow = EmotionGroupTable->FindRow<FAwAgentEmotionalAbilityGroupProfile>(GroupID, TEXT("Emotion Group Lookup")))
	{
		AbilityGroup = PermissionGroupRow->AbilityGroup;
		EmotionGroupID = GroupID;
		CalculateNavCosts();
	}
	else
	{
		checkf(false, TEXT("Invalid Emotion GroupID"));
	}
}

void UAwAgentEmotionProfileComponent::AdjustEmotion(const EEmotionalAbilityType AbilityType, const int32 Delta, const float AdjustTime)
{
	FEmotionalAbilityGroup TempAbilityGroup = AbilityGroup;
	switch (AbilityType) {
	case EEmotionalAbilityType::Courage:
		AbilityGroup.Courage += Delta;
		break;
	case EEmotionalAbilityType::ComfortSeeking:
		AbilityGroup.ComfortSeeking += Delta;
		break;
	case EEmotionalAbilityType::Memory:
		AbilityGroup.Memory += Delta;
		break;
	}
	CalculateNavCosts();

	if (AdjustTime > 0.0f)
	{
		TWeakObjectPtr WeakThis(this);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			FTimerDelegate::CreateLambda([WeakThis, TempAbilityGroup]()
			{
				if (!WeakThis.IsValid())
				{
					return;
				}

				WeakThis->AbilityGroup = TempAbilityGroup;
				WeakThis->CalculateNavCosts();
			}),
			AdjustTime,
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
