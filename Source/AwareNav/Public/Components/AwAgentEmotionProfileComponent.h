#pragma once

#include "CoreMinimal.h"
#include "Actors/AwEmotionAreaVolume.h"
#include "Components/ActorComponent.h"

#include "AwAgentEmotionProfileComponent.generated.h"

class UAwEmotionNavArea_Base;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEnteredEmotionVolume, AAwEmotionAreaVolume*, EmotionAreaVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnLeftEmotionVolume, AAwEmotionAreaVolume*, EmotionAreaVolume);

UCLASS( meta=(BlueprintSpawnableComponent) )
class AWARENAV_API UAwAgentEmotionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="AwareNav|Emotions")
	FName EmotionGroupID;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Emotions")
	FOnEnteredEmotionVolume OnEnteredEmotionVolume;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Emotions")
	FOnLeftEmotionVolume OnLeftEmotionVolume;
	
	UPROPERTY()
	TObjectPtr<UDataTable> EmotionGroupTable = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UAwEmotionNavArea_Base>, float> EmotionalAreaCostMultipliers;

	UPROPERTY()
	TSet<AAwEmotionAreaVolume*> AreasAgentIsIn;

public:
	UAwAgentEmotionProfileComponent();

	TMap<TSubclassOf<UAwEmotionNavArea_Base>, float> GetEmotionalAreaCostMultipliers() const {return EmotionalAreaCostMultipliers;}

	void SetAgentEmotionGroupProfile(const FName GroupID);
	
	void EnterEmotionVolume(AAwEmotionAreaVolume* EmotionAreaVolume);
	void LeaveEmotionVolume(AAwEmotionAreaVolume* EmotionAreaVolume);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};