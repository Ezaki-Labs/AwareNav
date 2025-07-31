#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AwAgentPermissionGroupProfile.generated.h"

/**
 * @brief DataTable row representing an agent's permissions set group profile.
 *
 * This struct is used to define a named group of permissions for agents,
 * allowing designers to assign and manage permissions via DataTables.
 */
USTRUCT(BlueprintType)
struct AWARENAV_API FAwAgentPermissionGroupProfile : public FTableRowBase
{
	GENERATED_BODY()

	/** The set of permissions for this group profile. */
	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "/Script/AwareNav.EAwPermissionLevel", ToolTip = "The set of permissions for this group profile."))
	uint8 PermissionLevels = 0;
};
