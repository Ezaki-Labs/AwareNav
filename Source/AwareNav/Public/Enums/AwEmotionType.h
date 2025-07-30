#pragma once

#include "CoreMinimal.h"

/**
 * Represents the types of emotions that can influence navigation in the AwareNav plugin.
 */
UENUM(BlueprintType)
enum class EAwEmotionType : uint8
{
    /** No emotion (default/neutral). */
    None				UMETA(Hidden),

    /** Fear emotion, typically increases navigation cost for agents sensitive to fear. */
    Fear				UMETA(DisplayName = "Fear"),

    /** Haunting emotion, can influence agents to avoid certain areas. */
    Haunting				UMETA(DisplayName = "Haunting"),

    /** Safety emotion, typically decreases navigation cost for agents seeking safety. */
    Safety				UMETA(DisplayName = "Safety"),

    /** Nostalgia emotion, can influence agents to prefer certain areas. */
    Nostalgia			UMETA(DisplayName = "Nostalgia"),
};
