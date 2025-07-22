#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AwareNavSettings.generated.h"

USTRUCT(BlueprintType)
struct FEmotionCostConfig
{
	GENERATED_BODY()

	FEmotionCostConfig() {}

	FEmotionCostConfig(const float InLowCost, const float InDefaultCost, const float InHighCost) : LowCost(InLowCost), DefaultCost(InDefaultCost), HighCost(InHighCost) {}

	UPROPERTY(EditAnywhere, Config)
	float LowCost = 1.0f;

	UPROPERTY(EditAnywhere, Config)
	float DefaultCost = 0.5f;

	UPROPERTY(EditAnywhere, Config)
	float HighCost = 0.5f;
};

UCLASS(Config=AwareNav, DefaultConfig)
class AWARENAV_API UAwareNavSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Permissions")
	bool bEnablePermissionSystem = true;

	UPROPERTY(Config, EditAnywhere, Category="Permissions", meta=(ToolTip="Assign your permission group DataTable asset here.", RowType = "FAwAgentPermissionGroupProfile"))
	TSoftObjectPtr<UDataTable> PermissionGroupProfilesTable;
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions")
	bool bEnableEmotionSystem = true;

	UPROPERTY(Config, EditAnywhere, Category="Permissions", meta=(ToolTip="Assign your emotion group DataTable asset here.", RowType = "FAwAgentEmotionGroupProfile"))
	TSoftObjectPtr<UDataTable> EmotionGroupProfilesTable;
	
	UPROPERTY(Config, EditAnywhere, Category="EmotionNav", meta = (bEnableEmotionSystem = "true"))
	FEmotionCostConfig FearCost {3.0f, 5.0f, 7.0f};
	
	UPROPERTY(Config, EditAnywhere, Category="EmotionNav", meta = (bEnableEmotionSystem = "true"))
	FEmotionCostConfig SafetyCost {0.7f, 0.5f, 0.3f};
	
	UPROPERTY(Config, EditAnywhere, Category="EmotionNav", meta = (bEnableEmotionSystem = "true"))
	FEmotionCostConfig NostalgiaCost {1.0f, 0.7f, 0.5f};
};