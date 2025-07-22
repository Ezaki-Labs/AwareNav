#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AwAgentEmotionProfileComponent.generated.h"

class UAwEmotionalNavArea_Base;

UCLASS()
class AWARENAV_API UAwAgentEmotionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseIndividualEmotionProfile = false;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "!bUseIndividualEmotionProfile"))
	FDataTableRowHandle EmotionGroupProfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseIndividualEmotionProfile"))
	TMap<TSubclassOf<UAwEmotionalNavArea_Base>, float> EmotionalAreaCostMultipliers;

public:
	UAwAgentEmotionProfileComponent();

	TMap<TSubclassOf<UAwEmotionalNavArea_Base>, float> GetEmotionalAreaCostMultipliers() const {return EmotionalAreaCostMultipliers;}
	
protected:
	virtual void BeginPlay() override;
};