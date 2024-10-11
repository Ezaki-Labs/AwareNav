#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "Enums/PermissionEnum.h"

#include "RestrictedNavigationComponent.generated.h"

UCLASS( meta=(BlueprintSpawnableComponent) )
class RESTRICTEDNAVIGATION_API URestrictedNavigationComponent : public UActorComponent
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="Restricted Navigation Component")
    FDataTableRowHandle NavigationTemplate;
	
	TSubclassOf<URestrictedNavigationQueryFilter_Base> NavQueryFilter;

	uint8 PermissionLevels = 0;

public:	
	URestrictedNavigationComponent();

	uint8 GetPermissionLevels() {return PermissionLevels;}

	UFUNCTION(BlueprintCallable, Category="Restricted Navigation Component")
	TSubclassOf<URestrictedNavigationQueryFilter_Base> GetNavQueryFilter() {return NavQueryFilter;}
	
protected:
	virtual void BeginPlay() override;
};
