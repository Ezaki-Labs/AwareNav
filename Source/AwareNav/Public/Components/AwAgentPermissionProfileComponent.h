#pragma once

#include "CoreMinimal.h"
#include "Actors/AwRestrictedAreaVolume.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "AwAgentPermissionProfileComponent.generated.h"

class UAwRestrictedNavigationQueryFilter;
class AAwRestrictedAreaVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEnteredRestrictedVolume, AAwRestrictedAreaVolume*, RestrictedAreaVolume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnLeftRestrictedVolume, AAwRestrictedAreaVolume*, RestrictedAreaVolume);

/**
 * @brief Component that manages agent permission profiles and restricted area interactions.
 *
 * UAwAgentPermissionProfileComponent handles the assignment of permission groups to agents,
 * tracks which restricted areas the agent is currently inside, and broadcasts events when
 * the agent enters or leaves restricted volumes. It also provides access to the agent's
 * current permission levels.
 */
UCLASS(ClassGroup=(AwareNav), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class AWARENAV_API UAwAgentPermissionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	/** 
	 * Identifier for the permission group assigned to this agent.
	 */
	UPROPERTY(EditAnywhere, Category="AwareNav|Permissions", meta=(ToolTip="The unique ID of the permission group profile for this agent."))
	FName PermissionGroupID;
	
	/**
	 * Event triggered when the agent enters a restricted volume.
	 */
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions", meta=(ToolTip="Called when the agent enters a restricted area volume."))
	FOnEnteredRestrictedVolume OnEnteredRestrictedVolume;
	
	/**
	 * Event triggered when the agent leaves a restricted volume.
	 */
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions", meta=(ToolTip="Called when the agent leaves a restricted area volume."))
	FOnLeftRestrictedVolume OnLeftRestrictedVolume;
	
	/**
	 * Data table containing permission group definitions.
	 */
	UPROPERTY()
	TObjectPtr<UDataTable> PermissionGroupTable = nullptr;
	
	/**
	 * Bitmask representing the agent's current permission levels.
	 */
	uint8 PermissionLevels = 0;

	/**
	 * Set of restricted area volumes the agent is currently inside.
	 */
	UPROPERTY()
	TSet<AAwRestrictedAreaVolume*> AreasAgentIsIn;

public:	
	UAwAgentPermissionProfileComponent();

	/**
	 * Gets the agent's current permission levels.
	 * @return The permission levels as a bitmask.
	 */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Gets permission levels."))
	uint8 GetPermissionLevels() const {return PermissionLevels;}

	/**
	 * Assigns a new permission group profile to the agent.
	 * @param GroupID The identifier of the permission group to assign.
	 */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Assigns a permission group profile to the agent."))
	void SetAgentPermissionGroupProfile(const FName GroupID);

	/**
	 * Gets permission group profile ID of the agent.
	 * @return Permission group ID.
	 */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Gets permission group profile ID of the agent."))
	FName GetAgentPermissionGroupProfile() const {return PermissionGroupID;}

	/**
	 * Checks if the character has permission to be here.
	 * @return Check result.
	 */
    UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions", meta = (ToolTip = "Checks if the character has permission to be here."))
	bool DoesHavePermissionToBeHere();
	
	/**
	 * Notifies the component that the agent has entered a restricted area volume.
	 * @param RestrictedAreaVolume The volume the agent has entered.
	 */
	void EnterPermissionVolume(AAwRestrictedAreaVolume* RestrictedAreaVolume);

	/**
	 * Notifies the component that the agent has left a restricted area volume.
	 * @param RestrictedAreaVolume The volume the agent has left.
	 */
	void LeavePermissionVolume(AAwRestrictedAreaVolume* RestrictedAreaVolume);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
