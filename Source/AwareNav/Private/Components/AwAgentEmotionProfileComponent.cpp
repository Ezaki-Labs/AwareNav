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

void UAwAgentEmotionProfileComponent::CalculateFearNavCost(int32 Courage)
{
	Courage = FMath::Clamp(Courage, 1, 20);

	float FearNavCost = 1.0f;
	if (Courage > 10)
	{
		// From 10 to 20 → 1.0 → 0.5
		const float T = (Courage - 10) / 10.0f;
		FearNavCost = FMath::Lerp(1.0f, 0.5f, T);
	}
	else if (Courage < 10)
	{
		// From 10 to 1 → 1.0 → 3.0
		const float T = (10 - Courage) / 9.0f;
		FearNavCost = FMath::Lerp(1.0f, 3.0f, T);
	}
	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Fear::StaticClass(), FearNavCost);
}

void UAwAgentEmotionProfileComponent::CalculateSafetyNavCost(int32 ComfortSeeking)
{
	ComfortSeeking = FMath::Clamp(ComfortSeeking, 1, 20);

	const float T = (ComfortSeeking - 1) / 19.0f; // Range: 0.0 to 1.0
	const float SafetyNavCost =  FMath::Lerp(1.0f, 0.3f, T);
	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Safety::StaticClass(), SafetyNavCost);
}

void UAwAgentEmotionProfileComponent::CalculateMemoryBasedNavCosts(int32 Memory)
{
	Memory = FMath::Clamp(Memory, 1, 20);
	const float T = (Memory - 1) / 19.0f;
	
	const float FearNavCost = EmotionAreaCosts.FindOrAdd(UAwEmotionNavArea_Fear::StaticClass(), 1.0f); // 0.5–3.0
	const float HauntingNavCost = FMath::Lerp(1.0f, FearNavCost, T);	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Haunting::StaticClass(), HauntingNavCost);
	
	const float SafetyNavCost = EmotionAreaCosts.FindOrAdd(UAwEmotionNavArea_Safety::StaticClass(), 1.0f); // 0.3–1.0
	const float NostalgiaNavCost = FMath::Lerp(1.0f, SafetyNavCost, T);	
	EmotionAreaCosts.Add(UAwEmotionNavArea_Nostalgia::StaticClass(), NostalgiaNavCost);	
}

void UAwAgentEmotionProfileComponent::SetAgentEmotionGroupProfile(const FName GroupID)
{
	if (GroupID.IsNone())
	{
		return;
	}

	if (const FAwAgentEmotionGroupProfile* PermissionGroupRow = EmotionGroupTable->FindRow<FAwAgentEmotionGroupProfile>(GroupID, TEXT("Emotion Group Lookup")))
	{
		CalculateFearNavCost(PermissionGroupRow->Courage);
		CalculateSafetyNavCost(PermissionGroupRow->ComfortSeeking);
		CalculateMemoryBasedNavCosts(PermissionGroupRow->Memory);
	}
	else
	{
		checkf(false, TEXT("Invalid Emotion GroupID"));
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
