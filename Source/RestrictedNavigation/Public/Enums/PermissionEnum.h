#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPermissionLevel : uint8
{
    None                   = 0         UMETA(DisplayName = "None"),
    PermissionLevel_Low1      = 1 << 0    UMETA(DisplayName = "Permission Level Low 1"),
    PermissionLevel_Low2      = 1 << 1    UMETA(DisplayName = "Permission Level Low 2"),
    PermissionLevel_Mid1      = 1 << 2    UMETA(DisplayName = "Permission Level Mid 1"),
    PermissionLevel_Mid2      = 1 << 3    UMETA(DisplayName = "Permission Level Mid 2"),
    PermissionLevel_Mid3      = 1 << 4    UMETA(DisplayName = "Permission Level Mid 3"),
    PermissionLevel_Mid4      = 1 << 5    UMETA(DisplayName = "Permission Level Mid 4"),
    PermissionLevel_High1      = 1 << 6    UMETA(DisplayName = "Permission Level High 1"),
    PermissionLevel_High2      = 1 << 7    UMETA(DisplayName = "Permission Level High 2")
};
ENUM_CLASS_FLAGS(EPermissionLevel);
