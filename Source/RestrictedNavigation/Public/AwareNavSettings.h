#pragma once

#include "CoreMinimal.h"

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

	UPROPERTY(Config, EditAnywhere, Category="Permissions", meta=(ToolTip="Assign your permission group DataTable asset here.", RowType = "FAwAgentPermissionGroupProfile", EditCondition = "bEnablePermissionSystem"))
	TSoftObjectPtr<UDataTable> PermissionGroupProfilesTable;
	TSoftObjectPtr<UDataTable> CachedPermissionTable;
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions")
	bool bEnableEmotionSystem = true;

	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta=(ToolTip="Assign your emotion group DataTable asset here.", RowType = "FAwAgentEmotionGroupProfile", EditCondition = "bEnableEmotionSystem"))
	TSoftObjectPtr<UDataTable> EmotionGroupProfilesTable;
	TSoftObjectPtr<UDataTable> CachedEmotionTable;
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta = (EditCondition = "bEnableEmotionSystem"))
	FEmotionCostConfig FearCost {3.0f, 5.0f, 7.0f};
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta = (EditCondition = "bEnableEmotionSystem"))
	FEmotionCostConfig SafetyCost {0.7f, 0.5f, 0.3f};
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta = (EditCondition = "bEnableEmotionSystem"))
	FEmotionCostConfig NostalgiaCost {1.0f, 0.7f, 0.5f};

protected:
#if WITH_EDITOR
	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	template<typename RowType>
	bool ValidateTable(const TSoftObjectPtr<UDataTable>& TablePtr, const FString& PropertyName);
#endif
};
