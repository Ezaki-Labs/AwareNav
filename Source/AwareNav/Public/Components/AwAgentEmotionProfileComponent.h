#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Data/AwAgentEmotionalAbilityGroupProfile.h"
#include "Enums/AwEmotionType.h"

#include "AwAgentEmotionProfileComponent.generated.h"

class AAwEmotionAreaVolume;
class UAwEmotionNavArea_Base;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEnteredEmotionVolume, AAwEmotionAreaVolume*, EmotionAreaVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnLeftEmotionVolume, AAwEmotionAreaVolume*, EmotionAreaVolume);

/**
 * @brief Component that manages the emotional profile of an agent, including emotion group assignment,
 *        emotion area cost multipliers, and event dispatching for entering/leaving emotion volumes.
 *
 * This component allows an agent to have an emotion group profile, respond to emotion area volumes,
 * and provides Blueprint events for emotion volume interactions. It also manages cost multipliers
 * for different emotional areas, which can affect navigation or behavior.
 */
UCLASS(ClassGroup=(AwareNav), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class AWARENAV_API UAwAgentEmotionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	/** The identifier for the emotion group profile assigned to this agent. */
	UPROPERTY(EditAnywhere, Category="AwareNav|Emotions", meta=(ToolTip="The identifier for the emotion group profile assigned to this agent."))
	FName EmotionGroupID;
	
	/** Event triggered when the agent enters an emotion area volume. */
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Emotions", meta=(ToolTip="Event triggered when the agent enters an emotion area volume."))
	FOnEnteredEmotionVolume OnEnteredEmotionVolume;
	
	/** Event triggered when the agent leaves an emotion area volume. */
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Emotions", meta=(ToolTip="Event triggered when the agent leaves an emotion area volume."))
	FOnLeftEmotionVolume OnLeftEmotionVolume;
	
	/** Data table containing emotion group profiles and their associated data. */
	UPROPERTY()
	TObjectPtr<UDataTable> EmotionGroupTable = nullptr;

	/** Mapping of emotion types to their area cost multipliers for this agent. */
	UPROPERTY()
	TMap<UClass*, float> EmotionAreaCosts;

	/** Set of emotion area volumes the agent is currently inside. */
	UPROPERTY()
	TSet<AAwEmotionAreaVolume*> AreasAgentIsIn;

	/** The set of emotional abilities. */
	FEmotionalAbilityGroup AbilityGroup;

public:
	UAwAgentEmotionProfileComponent();

	/**
	 * Gets the current emotion area cost multipliers for this agent.
	 * @return Map of emotion types to cost multipliers.
	 */
	TMap<UClass*, float> GetEmotionalAreaCosts() const {return EmotionAreaCosts;}

	/**
	 * Sets the emotion group profile for this agent.
	 * @param GroupID The identifier of the emotion group to assign.
	 */
	void SetAgentEmotionGroupProfile(const FName GroupID);
	
	/**
	 * Adjust
	 * @param AbilityType 
	 * @param Delta 
	 * @param AdjustTime 
	 */
	void AdjustEmotion(const EEmotionalAbilityType AbilityType, const int32 Delta, const float AdjustTime = 0.0f);
	
	/**
	 * Notifies the component that the agent has entered an emotion area volume.
	 * @param EmotionAreaVolume The volume the agent has entered.
	 */
	void EnterEmotionVolume(AAwEmotionAreaVolume* EmotionAreaVolume);

	/**
	 * Notifies the component that the agent has left an emotion area volume.
	 * @param EmotionAreaVolume The volume the agent has left.
	 */
	void LeaveEmotionVolume(AAwEmotionAreaVolume* EmotionAreaVolume);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/**
	 * Calculates nav costs based on emotional abilities.
	 */
	void CalculateNavCosts();
};