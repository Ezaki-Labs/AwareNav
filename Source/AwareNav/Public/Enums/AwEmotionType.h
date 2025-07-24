#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAwEmotionType : uint8
{
	None				UMETA(Hidden),
	Fear				UMETA(DisplayName = "Fear"),
	Safety				UMETA(DisplayName = "Safety"),
	Nostalgia			UMETA(DisplayName = "Nostalgia"),
};
