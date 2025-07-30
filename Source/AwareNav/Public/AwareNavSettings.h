#pragma once

#include "CoreMinimal.h"

#include "AwareNavSettings.generated.h"

/**
 * Settings for the AwareNav plugin.
 */
UCLASS(Config=AwareNav, DefaultConfig)
class AWARENAV_API UAwareNavSettings : public UObject
{
	GENERATED_BODY()

public:
#pragma region Permissions
	/** Enables or disables the permission system for navigation. */
	UPROPERTY(Config, EditAnywhere, Category="Permissions", meta=(ToolTip="Enables or disables the permission system for navigation."))
	bool bEnablePermissionSystem = true;

	/** Assign your permission group DataTable asset here. Should contain FAwAgentPermissionGroupProfile rows. */
	UPROPERTY(Config, EditAnywhere, Category="Permissions", meta=(ToolTip="Assign your permission group DataTable asset here. Should contain FAwAgentPermissionGroupProfile rows.", RowType = "FAwAgentPermissionGroupProfile", EditCondition = "bEnablePermissionSystem"))
	TSoftObjectPtr<UDataTable> PermissionGroupProfilesTable;

	/** Cached DataTable for permissions. Used internally. */
	TSoftObjectPtr<UDataTable> CachedPermissionTable;
#pragma endregion
	
#pragma region Emotions	
	/** Enables or disables the emotion system for navigation. */
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta=(ToolTip="Enables or disables the emotion system for navigation."))
	bool bEnableEmotionSystem = true;

	/** Assign your emotion group DataTable asset here. Should contain FAwAgentEmotionGroupProfile rows. */
	UPROPERTY(Config, EditAnywhere, Category="Emotions", meta=(ToolTip="Assign your emotion group DataTable asset here. Should contain FAwAgentEmotionGroupProfile rows.", RowType = "FAwAgentEmotionGroupProfile", EditCondition = "bEnableEmotionSystem"))
	TSoftObjectPtr<UDataTable> EmotionGroupProfilesTable;

	/** Cached DataTable for emotions. Used internally. */
	TSoftObjectPtr<UDataTable> CachedEmotionTable;
#pragma endregion

protected:
#if WITH_EDITOR
	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	/**
	 * Validates the given DataTable asset for the specified row type.
	 * @param TablePtr The DataTable asset pointer.
	 * @param PropertyName The name of the property being validated.
	 * @return true if the table is valid, false otherwise.
	 */
	template<typename RowType>
	bool ValidateTable(const TSoftObjectPtr<UDataTable>& TablePtr, const FString& PropertyName);
#endif
};
