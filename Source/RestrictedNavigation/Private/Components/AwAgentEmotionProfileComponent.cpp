#include "Components/AwAgentEmotionProfileComponent.h"

#include "Data/AwAgentEmotionGroupProfile.h"

UAwAgentEmotionProfileComponent::UAwAgentEmotionProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAwAgentEmotionProfileComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!bUseIndividualEmotionProfile)
	{
		if (FAwAgentEmotionGroupProfile* NavigationPermissionsTemplate = EmotionGroupProfile.GetRow<FAwAgentEmotionGroupProfile>(TEXT("Getting Data")))
		{
			EmotionalAreaCostMultipliers = NavigationPermissionsTemplate->EmotionalAreaCostMultipliers;
		}		
	}
}
