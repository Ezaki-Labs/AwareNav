#pragma once

#include "CoreMinimal.h"
#include "NavFilters/NavigationQueryFilter.h"

#include "AwNavigationQueryFilter.generated.h"

UCLASS(ClassGroup=(AwareNav), BlueprintType, Blueprintable)
class AWARENAV_API UAwNavigationQueryFilter : public UNavigationQueryFilter
{
	GENERATED_BODY()

public:
	UAwNavigationQueryFilter();
	
protected:
	virtual void InitializeFilter(const ANavigationData& NavData, const UObject* Querier, FNavigationQueryFilter& Filter) const override;
};
