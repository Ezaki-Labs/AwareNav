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

/**
 * Represents the types of emotional abilities that are used to modulate how agents react to different emotion areas.
 */
UENUM(BlueprintType)
enum class EEmotionalAbilityType : uint8
{
    /** Agent's courage, typically reduces the effect of fear-based emotion areas. */
    Courage         UMETA(DisplayName = "Courage"),

    /** Agent's tendency to seek comfort or safety, increases attraction to safety areas. */
    ComfortSeeking  UMETA(DisplayName = "Comfort Seeking"),
    
    /** Agent's memory, affects on nostalgia and haunting areas. */
    Memory          UMETA(DisplayName = "Memory"),

    // Future entries:
    // Empathy,
    // Resilience,
    // Awareness,
};
