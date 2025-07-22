#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AwAgentPermissionGroupProfile.generated.h"

USTRUCT(BlueprintType)
struct AWARENAV_API FAwAgentPermissionGroupProfile : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script/AwareNav.EAwPermissionLevel"))
	uint8 PermissionLevels = 0;
};
