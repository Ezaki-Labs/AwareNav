#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "AwAgentPermissionProfileComponent.generated.h"

class UAwRestrictedNavigationQueryFilter;

UCLASS( meta=(BlueprintSpawnableComponent) )
class AWARENAV_API UAwAgentPermissionProfileComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="AwareNav|Permissions")
	FName PermissionGroupID;
	UPROPERTY()
	TObjectPtr<UDataTable> PermissionGroupTable = nullptr;
	
	uint8 PermissionLevels = 0;

public:	
	UAwAgentPermissionProfileComponent();

	uint8 GetPermissionLevels() const {return PermissionLevels;}

	void SetAgentPermissionGroupProfile(const FName GroupID);
	
protected:
	virtual void BeginPlay() override;
};
