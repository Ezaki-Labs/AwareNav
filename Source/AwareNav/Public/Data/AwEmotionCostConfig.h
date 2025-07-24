#pragma once

#include "CoreMinimal.h"

#include "AwEmotionCostConfig.generated.h"

USTRUCT(BlueprintType)
struct FAwEmotionCostConfig
{
	GENERATED_BODY()

	FAwEmotionCostConfig() {}

	FAwEmotionCostConfig(const float InDefaultCost, const float InLowCost, const float InHighCost) : DefaultCost(InDefaultCost), LowCost(InLowCost), HighCost(InHighCost) {}

	UPROPERTY(EditAnywhere, Config)
	float DefaultCost = 1.0f;

	UPROPERTY(EditAnywhere, Config)
	float LowCost = 1.0f;

	UPROPERTY(EditAnywhere, Config)
	float HighCost = 1.0f;
};