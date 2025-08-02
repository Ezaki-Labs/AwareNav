#pragma once

#include "CoreMinimal.h"
#include "NavModifierVolume.h"

#include "Enums/AwPermissionLevel.h"

#include "AwRestrictedAreaVolume.generated.h"

class UBillboardComponent;
class UTextRenderComponent;
class UAwAgentPermissionProfileComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorEnteredRestrictedArea, AActor*, Agent, UAwAgentPermissionProfileComponent*, AgentPermissionProfileComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorLeftRestrictedArea, AActor*, Agent, UAwAgentPermissionProfileComponent*, AgentPermissionProfileComponent);

/**
 * @brief Represents a restricted navigation area that enforces agent permission checks.
 *
 * This volume defines a box-shaped restricted area in the world. Agents with permission profiles
 * are checked for access when entering or leaving the area. The area can broadcast events for
 * entering and leaving, and supports runtime permission level changes.
 */
UCLASS(ClassGroup=(AwareNav), BlueprintType, Blueprintable)
class AWARENAV_API AAwRestrictedAreaVolume : public ANavModifierVolume
{
    GENERATED_BODY()

    /** The permission level required to enter this area. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ToolTip = "The permission level required to enter this area."), Category="AwareNav|Permissions")
    EAwPermissionLevel PermissionLevel = EAwPermissionLevel::None;
    
    /** Called when an agent enters the restricted area. */
    UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions", meta = (ToolTip = "Called when an agent enters the restricted area."))
    FOnActorEnteredRestrictedArea OnActorEntered;
    
    /** Called when an agent leaves the restricted area. */
    UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions", meta = (ToolTip = "Called when an agent leaves the restricted area."))
    FOnActorLeftRestrictedArea OnActorLeft;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="AwareNav|Permissions")
    FText EditorOnlyLabel = FText::FromString(TEXT("Restricted Area"));
    
    UPROPERTY()
    UBillboardComponent* EditorOnlyBillboard = nullptr;
    
    UPROPERTY()
    UTextRenderComponent* EditorLabel;
#endif
    
    /** Box trigger volume for overlap detection. */
    UPROPERTY()
    class UBoxComponent* TriggerVolume;

    /** Whether the permission system is enabled for this area. */
    bool bPermissionSystemEnabled = false;

    /** Set of agent permission profile components currently inside the area. */
    UPROPERTY()
    TSet<UAwAgentPermissionProfileComponent*> AgentsInArea;

public:
    AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer);

    /**
     * Set the permission level for this area.
     * @param NewPermissionLevel The new permission level to assign.
     */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Sets the permission level for this area."))
    void SetPermissionLevel(EAwPermissionLevel NewPermissionLevel);

    /**
     * Gets the permission level of this area.
     * @return Permission level.
     */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Gets the permission level of this area."))
    EAwPermissionLevel GetPermissionLevel() const  { return PermissionLevel; }

    /**
     * Force an agent to leave the area.
     * @param AgentPermissionProfileComponent The agent's permission profile component.
     */
    void ForceLeaveArea(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    /** Called when an agent enters the area. */
    void ActorEntered(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

    /** Called when an agent leaves the area. */
    void ActorLeft(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

    /** Updates the trigger volume size to match the area. */
    void UpdateTriggerVolumeSize() const;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
    virtual void PostEditMove(bool bFinished) override;
#endif
};
