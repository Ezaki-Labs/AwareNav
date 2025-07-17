#pragma once

#include "CoreMinimal.h"
#include "NavFilters/NavigationQueryFilter.h"

#include "NavigationQueryFilters.generated.h"

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter : public UNavigationQueryFilter
{
	GENERATED_BODY()

public:
	URestrictedNavigationQueryFilter();
	
protected:
	virtual void InitializeFilter(const ANavigationData& NavData, const UObject* Querier, FNavigationQueryFilter& Filter) const override;
};
