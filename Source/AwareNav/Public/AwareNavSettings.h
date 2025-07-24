#pragma once

#include "CoreMinimal.h"

#include "Data/AwEmotionCostConfig.h"

#include "AwareNavSettings.generated.h"

UCLASS(Config=AwareNav, DefaultConfig)
class AWARENAV_API UAwareNavSettings : public UObject
{
	GENERATED_BODY()

public:
#pragma region Permissions
	UPROPERTY(Config, EditAnywhere, Category="Permissions")
	bool bEnablePermissionSystem = true;

	UPROPERTY(Config, EditAnywhere, Category="Permissions", meta=(ToolTip="Assign your permission group DataTable asset here.", RowType = "FAwAgentPermissionGroupProfile", EditCondition = "bEnablePermissionSystem"))
	TSoftObjectPtr<UDataTable> PermissionGroupProfilesTable;
	TSoftObjectPtr<UDataTable> CachedPermissionTable;
#pragma endregion
	
#pragma region Emotions	
	UPROPERTY(Config, EditAnywhere, Category="Emotions")
	bool bEnableEmotionSystem = true;

	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta=(ToolTip="Assign your emotion group DataTable asset here.", RowType = "FAwAgentEmotionGroupProfile", EditCondition = "bEnableEmotionSystem"))
	TSoftObjectPtr<UDataTable> EmotionGroupProfilesTable;
	TSoftObjectPtr<UDataTable> CachedEmotionTable;
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta = (EditCondition = "bEnableEmotionSystem"))
	FAwEmotionCostConfig FearCost {3.0f, 5.0f, 7.0f};
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta = (EditCondition = "bEnableEmotionSystem"))
	FAwEmotionCostConfig SafetyCost {0.7f, 0.5f, 0.3f};
	
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta = (EditCondition = "bEnableEmotionSystem"))
	FAwEmotionCostConfig NostalgiaCost {1.0f, 0.7f, 0.5f};
#pragma endregion

protected:
#if WITH_EDITOR
	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	template<typename RowType>
	bool ValidateTable(const TSoftObjectPtr<UDataTable>& TablePtr, const FString& PropertyName);
#endif
};
