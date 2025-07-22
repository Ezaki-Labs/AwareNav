#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AwAgentEmotionGroupProfile.generated.h"

class UAwEmotionalNavArea_Base;

USTRUCT(BlueprintType)
struct AWARENAV_API FAwAgentEmotionGroupProfile : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UAwEmotionalNavArea_Base>, float> EmotionalAreaCostMultipliers;
};
