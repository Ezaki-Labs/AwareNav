#include "AwareNavSettings.h"

#include "Engine/DataTable.h"

#include "Data/AwAgentEmotionalAbilityGroupProfile.h"
#include "Data/AwAgentPermissionGroupProfile.h"

#if WITH_EDITOR
void UAwareNavSettings::PostInitProperties()
{
	Super::PostInitProperties();

	// Cache current config values as initial "valid" values
	CachedPermissionTable = PermissionGroupProfilesTable;
	CachedEmotionTable = EmotionGroupProfilesTable;

	// Optionally validate on load
	ValidateTable<FAwAgentPermissionGroupProfile>(PermissionGroupProfilesTable, TEXT("PermissionGroupProfilesTable"));
	ValidateTable<FAwAgentEmotionalAbilityGroupProfile>(EmotionGroupProfilesTable, TEXT("EmotionGroupProfilesTable"));
}

void UAwareNavSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UAwareNavSettings, PermissionGroupProfilesTable))
	{
		if (!ValidateTable<FAwAgentPermissionGroupProfile>(PermissionGroupProfilesTable, TEXT("PermissionGroupProfilesTable")))
		{
			// Revert to previous
			Modify();
			PermissionGroupProfilesTable = CachedPermissionTable;
			UE_LOG(LogTemp, Warning, TEXT("[AwareNavSettings] Reverted PermissionGroupProfilesTable due to invalid row type."));
		}
		else
		{
			CachedPermissionTable = PermissionGroupProfilesTable;
		}
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAwareNavSettings, EmotionGroupProfilesTable))
	{
		if (!ValidateTable<FAwAgentEmotionalAbilityGroupProfile>(EmotionGroupProfilesTable, TEXT("EmotionGroupProfilesTable")))
		{
			Modify();
			EmotionGroupProfilesTable = CachedEmotionTable;
			UE_LOG(LogTemp, Warning, TEXT("[AwareNavSettings] Reverted EmotionGroupProfilesTable due to invalid row type."));
		}
		else
		{
			CachedEmotionTable = EmotionGroupProfilesTable;
		}
	}
}

template<typename RowType>
bool UAwareNavSettings::ValidateTable(const TSoftObjectPtr<UDataTable>& TablePtr, const FString& PropertyName)
{
	if (const UDataTable* Table = TablePtr.LoadSynchronous())
	{
		if (Table->GetRowStruct() != RowType::StaticStruct())
		{
			UE_LOG(LogTemp, Error, TEXT("[AwareNavSettings] %s has invalid row type: expected %s, got %s"),
				*PropertyName,
				*RowType::StaticStruct()->GetName(),
				*Table->GetRowStruct()->GetName()
			);
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Assigned DataTable has incorrect row type.")));
			return false;
		}
	}
	return true;
}
#endif
