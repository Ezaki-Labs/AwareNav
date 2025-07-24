#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Enums/AwEmotionType.h"
#include "Data/AwEmotionCostConfig.h"

#include "AwAgentEmotionGroupProfile.generated.h"

USTRUCT(BlueprintType)
struct AWARENAV_API FAwAgentEmotionGroupProfile : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<EAwEmotionType, FAwEmotionCostConfig> EmotionalAreaCostMultipliers;
};
