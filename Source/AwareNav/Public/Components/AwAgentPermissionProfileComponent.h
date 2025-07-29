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

UCLASS( meta=(BlueprintSpawnableComponent) )
class AWARENAV_API UAwAgentPermissionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="AwareNav|Permissions")
	FName PermissionGroupID;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions")
	FOnEnteredRestrictedVolume OnEnteredRestrictedVolume;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions")
	FOnLeftRestrictedVolume OnLeftRestrictedVolume;
	
	UPROPERTY()
	TObjectPtr<UDataTable> PermissionGroupTable = nullptr;
	
	uint8 PermissionLevels = 0;

	UPROPERTY()
	TSet<AAwRestrictedAreaVolume*> AreasAgentIsIn;

public:	
	UAwAgentPermissionProfileComponent();

	uint8 GetPermissionLevels() const {return PermissionLevels;}

	void SetAgentPermissionGroupProfile(const FName GroupID);
	
	void EnterPermissionVolume(AAwRestrictedAreaVolume* RestrictedAreaVolume);
	void LeavePermissionVolume(AAwRestrictedAreaVolume* RestrictedAreaVolume);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
