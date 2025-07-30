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
	if (!Area)
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

void UAwareNavSubsystem::BoostEmotion(const AActor* Agent, const EAwEmotionType EmotionType, const float BoostMultiplier)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentEmotionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->BoostEmotion(EmotionType, BoostMultiplier);
	}
}

void UAwareNavSubsystem::BoostEmotionTemporarily(const AActor* Agent, const EAwEmotionType EmotionType, const float BoostMultiplier, const float BoostTime)
{
	if (!IsValid(Agent))
	{
		return;
	}
	
	if (UAwAgentEmotionProfileComponent* PermissionProfileComponent = Agent->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(PermissionProfileComponent))
	{
		PermissionProfileComponent->BoostEmotion(EmotionType, BoostMultiplier, BoostTime);
	}
}

void UAwareNavSubsystem::SpawnEmotionArea(const FEmotionAreaSpawnParams& SpawnParams)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	AAwEmotionAreaVolume* Template = NewObject<AAwEmotionAreaVolume>();
	Template->SetAreaParams(SpawnParams.EmotionType, SpawnParams.Radius);

	FActorSpawnParameters Params;
	Params.Template = Template;
	
	if (AAwEmotionAreaVolume* Spawned = World->SpawnActor<AAwEmotionAreaVolume>(AAwEmotionAreaVolume::StaticClass(), SpawnParams.SpawnLocation, FRotator::ZeroRotator, Params))
	{
		if (SpawnParams.bHasLifeSpan)
		{
			Spawned->SetLifeSpan(SpawnParams.LifeSpan);
		}
		if (SpawnParams.bReducing)
		{
			Spawned->EnableAreaReducing(SpawnParams.ReduceIntervalInSeconds, SpawnParams.ReduceAmountPerInterval);
		}
	}
}
#pragma endregion
