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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseIndividualPermissionProfile = false;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "!bUseIndividualPermissionProfile"))
    FDataTableRowHandle PermissionGroupProfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseIndividualPermissionProfile", Bitmask, BitmaskEnum = "/Script/AwareNav.EAwPermissionLevel"))
	uint8 PermissionLevels = 0;

public:	
	UAwAgentPermissionProfileComponent();

	uint8 GetPermissionLevels() const {return PermissionLevels;}
	
protected:
	virtual void BeginPlay() override;
};
