#include "AwareNavSubsystem.h"

#include "Actors/AwEmotionAreaVolume.h"
#include "Actors/AwRestrictedAreaVolume.h"
#include "Components/AwAgentEmotionProfileComponent.h"
#include "Components/AwAgentPermissionProfileComponent.h"

#pragma region Initialize
void UAwareNavSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAwareNavSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
#pragma endregion

#pragma region Permissions
void UAwareNavSubsystem::SetAgentPermissionGroupProfile(const AActor* Agent, const FName GroupID)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentPermissionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->SetAgentPermissionGroupProfile(GroupID);
	}
}

void UAwareNavSubsystem::SetAreaPermission(AAwRestrictedAreaVolume* Area, const EAwPermissionLevel NewPermission)
{
	if (!IsValid(Area))
	{
		return;
	}

	Area->SetPermissionLevel(NewPermission);
}
#pragma endregion

#pragma region Emotions
void UAwareNavSubsystem::SetAgentEmotionGroupProfile(const AActor* Agent, const FName GroupID)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentEmotionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->SetAgentEmotionGroupProfile(GroupID);
	}
}

void UAwareNavSubsystem::AdjustEmotion(const AActor* Agent, const EEmotionalAbilityType AbilityType, const int32 Delta)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentEmotionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->AdjustEmotion(AbilityType, Delta);
	}	
}

void UAwareNavSubsystem::AdjustEmotionTemporarily(const AActor* Agent, const EEmotionalAbilityType AbilityType,
	const int32 Delta, const float AdjustTime)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentEmotionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->AdjustEmotion(AbilityType, Delta, AdjustTime);
	}	
}

void UAwareNavSubsystem::SpawnEmotionArea(const FEmotionAreaSpawnParams& SpawnParams)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	AAwEmotionAreaVolume::SpawnEmotionArea(World, SpawnParams);
}
#pragma endregion
