#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AwAgentEmotionProfileComponent.generated.h"

class UAwEmotionNavArea_Base;

UCLASS()
class AWARENAV_API UAwAgentEmotionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="AwareNav|Emotions")
	FName EmotionGroupID;
	UPROPERTY()
	TObjectPtr<UDataTable> EmotionGroupTable = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UAwEmotionNavArea_Base>, float> EmotionalAreaCostMultipliers;

public:
	UAwAgentEmotionProfileComponent();

	TMap<TSubclassOf<UAwEmotionNavArea_Base>, float> GetEmotionalAreaCostMultipliers() const {return EmotionalAreaCostMultipliers;}

	void SetAgentEmotionGroupProfile(const FName GroupID);
	
protected:
	virtual void BeginPlay() override;
};