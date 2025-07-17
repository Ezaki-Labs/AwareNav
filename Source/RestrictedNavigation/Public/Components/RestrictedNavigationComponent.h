#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "RestrictedNavigationComponent.generated.h"

class URestrictedNavigationQueryFilter;

UCLASS( meta=(BlueprintSpawnableComponent) )
class RESTRICTEDNAVIGATION_API URestrictedNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="Restricted Navigation Component")
	bool bUseIndividualPermissionLevels = false;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "!bUseIndividualPermissionLevels"), Category="Restricted Navigation Component")
    FDataTableRowHandle NavigationTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseIndividualPermissionLevels", Bitmask, BitmaskEnum = "/Script/RestrictedNavigation.EPermissionLevel"), Category="Restricted Navigation Component")
	uint8 PermissionLevels = 0;

public:	
	URestrictedNavigationComponent();

	uint8 GetPermissionLevels() const {return PermissionLevels;}
	
protected:
	virtual void BeginPlay() override;
};
