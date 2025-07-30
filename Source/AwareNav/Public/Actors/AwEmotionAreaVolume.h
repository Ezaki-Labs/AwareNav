#pragma once

#include "CoreMinimal.h"
#include "AwareNavSubsystem.h"
#include "GameFramework/Actor.h"

#include "Enums/AwEmotionType.h"

#include "AwEmotionAreaVolume.generated.h"

class UAwAgentEmotionProfileComponent;
class USphereComponent;
class AAwEmotionZone;
class UAwEmotionNavArea_Base;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorEnteredEmotionArea, AActor*, Agent, UAwAgentEmotionProfileComponent*, AgentEmotionProfileComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorLeftEmotionArea, AActor*, Agent, UAwAgentEmotionProfileComponent*, AgentEmotionProfileComponent);

/**
 * @brief Represents an emotion area in the world that influences agent navigation based on emotion type and intensity.
 *
 * This actor defines a spherical area with a specific emotion type and radius. Agents with emotion profiles
 * are affected when entering or leaving the area. The area can optionally shrink over time.
 */
UCLASS(ClassGroup=(AwareNav), BlueprintType, Blueprintable)
class AWARENAV_API AAwEmotionAreaVolume : public AActor
{
    GENERATED_BODY()

    /** Root scene component for the area volume. */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AwareNav|Emotions", meta = (AllowPrivateAccess = "true", ToolTip = "Root scene component for the area volume."))
    TObjectPtr<USceneComponent> Root = nullptr;

    /** The type of emotion this area represents. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AwareNav|Emotions", meta = (AllowPrivateAccess = "true", ToolTip = "The type of emotion this area represents."))
    EAwEmotionType EmotionType = EAwEmotionType::None;

    /** The radius of the emotion area. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AwareNav|Emotions", meta = (AllowPrivateAccess = "true", ClampMin = 0.0, ToolTip = "The radius of the emotion area."))
    float Radius = 500.0f;

    /** The radius of the emotion area. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AwareNav|Emotions", meta = (AllowPrivateAccess = "true", ClampMin = 0.0, ToolTip = "The radius of the emotion area."))
    float EmotionTriggerZoneRadiusMultiplier = 1.7f;

    /** Called when an agent enters the emotion area. */
    UPROPERTY(BlueprintAssignable, Category = "AwareNav|Emotions", meta = (ToolTip = "Called when an agent enters the emotion area."))
    FOnActorEnteredEmotionArea OnActorEntered;

    /** Called when an agent leaves the emotion area. */
    UPROPERTY(BlueprintAssignable, Category = "AwareNav|Emotions", meta = (ToolTip = "Called when an agent leaves the emotion area."))
    FOnActorLeftEmotionArea OnActorLeft;

    /** Whether the emotion system is enabled for this area. */
    bool bEmotionsSystemEnabled = false;

    /** Sphere trigger volume for overlap detection. */
    UPROPERTY()
    TObjectPtr<USphereComponent> TriggerVolume = nullptr;

    /** Child actor for the default intensity effect zone. */
    UPROPERTY()
    TObjectPtr<USphereComponent> NavZoneActor = nullptr;

    /** Amount to reduce the area radius per interval. */
    float ReduceAmountPerInterval = 0.0f;

    /** Set of agent emotion profile components currently inside the area. */
    UPROPERTY()
    TSet<UAwAgentEmotionProfileComponent*> AgentsInArea;

public:
    AAwEmotionAreaVolume();
    
    static AAwEmotionAreaVolume* SpawnEmotionArea(UWorld* World, const FEmotionAreaSpawnParams& SpawnParams);

    /**
     * Set the emotion type and radius for this area.
     * @param InEmotionType The emotion type to set.
     * @param InRadius The radius to set.
     */
    void SetAreaParams(const EAwEmotionType InEmotionType, const float InRadius);

    /**
     * Enable area shrinking over time.
     * @param ReduceIntervalInSeconds How often (in seconds) to reduce the area.
     * @param ReduceAmount How much to reduce the radius each interval.
     */
    void EnableAreaReducing(const float ReduceIntervalInSeconds, const float ReduceAmount);

    /**
     * Force an agent to leave the area.
     * @param AgentEmotionProfileComponent The agent's emotion profile component.
     */
    void ForceLeaveArea(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent);

protected:
    virtual void PostRegisterAllComponents() override;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** Update the emotion zones (e.g., after radius change). */
    void UpdateZones();

    /** Reduces the area radius at set intervals. */
    UFUNCTION()
    void ReduceArea();

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    /** Called when an agent enters the area. */
    void ActorEntered(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent);

    /** Called when an agent leaves the area. */
    void ActorLeft(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent);

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
