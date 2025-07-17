#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "NavQueryFilters/NavigationQueryFilters.h"

#include "NavigationPermissionsTemplate.generated.h"

USTRUCT(BlueprintType)
struct RESTRICTEDNAVIGATION_API FNavigationPermissionsTemplate : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script/RestrictedNavigation.EPermissionLevel"), Category = "Navigation Permissions Template")
	uint8 PermissionLevels = 0;
};
