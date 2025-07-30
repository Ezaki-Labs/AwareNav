#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Enums/AwEmotionType.h"
#include "Enums/AwPermissionLevel.h"

#include "AwareNavSubsystem.generated.h"

class AAwRestrictedAreaVolume;

#pragma region Emotion Structs
/**
 * Parameters for spawning an emotion area in the world.
 */
USTRUCT(BlueprintType)
struct FEmotionAreaSpawnParams
{
    GENERATED_BODY()

    /** World location where the emotion area will be spawned. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "World location where the emotion area will be spawned."))
    FVector SpawnLocation = FVector::ZeroVector;

    /** The type of emotion this area represents. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The type of emotion this area represents."))
    EAwEmotionType EmotionType = EAwEmotionType::None;

    /** The radius of the emotion area. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The radius of the emotion area."))
    float Radius = 400.0f;

    /** Whether the area should have a limited lifespan. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Whether the area should have a limited lifespan."))
    bool bHasLifeSpan = false;

    /** How long (in seconds) the area should exist if it has a lifespan. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How long (in seconds) the area should exist if it has a lifespan."))
    float LifeSpan = 5.0f;

    /** Whether the area should shrink over time. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "Whether the area should shrink over time."))
    bool bReducing = false;

    /** How often (in seconds) the area should shrink if reducing is enabled. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How often (in seconds) the area should shrink if reducing is enabled."))
    float ReduceIntervalInSeconds = 3.0f;

    /** How much the area radius should shrink each interval. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "How much the area radius should shrink each interval."))
    float ReduceAmountPerInterval = 20.0f;
};
#pragma endregion

/**
 * Main subsystem for the AwareNav plugin.
 * Handles agent permission and emotion group management, area permission assignment,
 * emotion boosting, and spawning of emotion areas.
 * Exposes BlueprintCallable functions for runtime interaction with the navigation and emotion systems.
 */
UCLASS(ClassGroup=(AwareNav))
class AWARENAV_API UAwareNavSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
#pragma region Initialize
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
#pragma endregion

#pragma region Permissions
    // ----------- Agent with UAwAgentPermissionProfileComponent -----------

    /**
     * Assigns a permission group profile to the specified agent.
     * @param Agent The agent actor to assign the group to.
     * @param GroupID The identifier of the permission group.
     */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Assigns a permission group profile to the specified agent."))
    void SetAgentPermissionGroupProfile(const AActor* Agent, const FName GroupID);

    // ----------- Restricted Area Volume -----------

    /**
     * Sets the permission level for a restricted area volume.
     * @param Area The restricted area volume to modify.
     * @param NewPermission The new permission level to assign.
     */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Sets the permission level for a restricted area volume."))
    void SetAreaPermission(AAwRestrictedAreaVolume* Area, const EAwPermissionLevel NewPermission);
#pragma endregion

#pragma region Emotions	
    // ----------- Agent with UAwAgentPermissionProfileComponent -----------

    /**
     * Assigns an emotion group profile to the specified agent.
     * @param Agent The agent actor to assign the group to.
     * @param GroupID The identifier of the emotion group.
     */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Emotions", meta = (ToolTip = "Assigns an emotion group profile to the specified agent."))
    void SetAgentEmotionGroupProfile(const AActor* Agent, const FName GroupID);

    // ----------- Emotion Area Volume -----------

    /**
     * Spawns a new emotion area in the world with the specified parameters.
     * @param SpawnParams Struct containing all parameters for the new emotion area.
     */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Emotions", meta = (ToolTip = "Spawns a new emotion area in the world with the specified parameters."))
    void SpawnEmotionArea(const FEmotionAreaSpawnParams& SpawnParams);
#pragma endregion
};
