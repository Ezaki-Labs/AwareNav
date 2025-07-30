#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AwEmotionZone.generated.h"

class UBoxComponent;
class UAwEmotionNavArea_Base;
class UNavModifierComponent;

/**
 * @brief An actor representing an emotional navigation zone in the world.
 *
 * AAwEmotionZone defines a spatial area that can affect navigation behavior based on emotional context.
 * It utilizes navigation modifiers and configurable radii to influence AI pathfinding within its bounds.
 */
UCLASS(NotBlueprintable, HideDropdown)
class AWARENAV_API AAwEmotionZone : public AActor
{
	GENERATED_BODY()

	/** The root scene component for this actor. */
	UPROPERTY()
	TObjectPtr<USceneComponent> Root = nullptr;

	/** Navigation modifier component used to alter navigation mesh properties. */
	UPROPERTY()
	TObjectPtr<UNavModifierComponent> NavModifier = nullptr;

	/** Array of box components defining the physical bounds of the emotion zone. */
	UPROPERTY()
	TArray<TObjectPtr<UBoxComponent>> Boxes;

	/** The navigation area class that determines the type of navigation modification applied. */
	UPROPERTY()
	TSubclassOf<UAwEmotionNavArea_Base> NavAreaClass = nullptr;

	/** The inner radius of the emotion zone, used for fine-tuning the affected area. */
	float InnerRadius = 0.0f;

	/** The outer radius of the emotion zone. */
	float OuterRadius = 0.0f;

public:
	AAwEmotionZone();

	/**
	 * @brief Sets the navigation area class and radii for the emotion zone.
	 * @param InNavAreaClass The navigation area class to use.
	 * @param InInnerRadius The inner radius of the zone.
	 * @param InOuterRadius The outer radius of the zone.
	 */
	void SetEmotionZoneParams(const TSubclassOf<UAwEmotionNavArea_Base>& InNavAreaClass, const float InInnerRadius, const float InOuterRadius);

	/**
	 * @brief Updates the zone's configuration and applies changes to navigation.
	 */
	void UpdateEmotionZone();

protected:
	virtual void BeginPlay() override;
	virtual void PostRegisterAllComponents() override;
};
