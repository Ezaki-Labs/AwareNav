#pragma once

#include "CoreMinimal.h"
#include "NavFilters/NavigationQueryFilter.h"

#include "NavigationQueryFilters.generated.h"

UCLASS(Abstract)
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter_Base : public UNavigationQueryFilter
{
	GENERATED_BODY()

public:
	URestrictedNavigationQueryFilter_Base();
	
protected:
	virtual void InitializeFilter(const ANavigationData& NavData, const UObject* Querier, FNavigationQueryFilter& Filter) const override;
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter1 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter2 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter3 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter4 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter5 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter6 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter7 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter8 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter9 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter10 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter11 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter12 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter13 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter14 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter15 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter16 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter17 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter18 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter19 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

UCLASS()
class RESTRICTEDNAVIGATION_API URestrictedNavigationQueryFilter20 : public URestrictedNavigationQueryFilter_Base
{
	GENERATED_BODY()
};

static TSubclassOf<URestrictedNavigationQueryFilter_Base> GetRestrictedNavigationQueryFilterByIndex(uint32 Index)
{
	if (Index == 0)
	{
		return URestrictedNavigationQueryFilter1::StaticClass();
	}
	else if (Index == 1)
	{
		return URestrictedNavigationQueryFilter2::StaticClass();
	}
	else if (Index == 2)
	{
		return URestrictedNavigationQueryFilter3::StaticClass();
	}
	else if (Index == 3)
	{
		return URestrictedNavigationQueryFilter4::StaticClass();
	}
	else if (Index == 4)
	{
		return URestrictedNavigationQueryFilter5::StaticClass();
	}
	else if (Index == 5)
	{
		return URestrictedNavigationQueryFilter6::StaticClass();
	}
	else if (Index == 6)
	{
		return URestrictedNavigationQueryFilter7::StaticClass();
	}
	else if (Index == 7)
	{
		return URestrictedNavigationQueryFilter8::StaticClass();
	}
	else if (Index == 8)
	{
		return URestrictedNavigationQueryFilter9::StaticClass();
	}
	else if (Index == 9)
	{
		return URestrictedNavigationQueryFilter10::StaticClass();
	}
	else if (Index == 10)
	{
		return URestrictedNavigationQueryFilter11::StaticClass();
	}
	else if (Index == 11)
	{
		return URestrictedNavigationQueryFilter12::StaticClass();
	}
	else if (Index == 12)
	{
		return URestrictedNavigationQueryFilter13::StaticClass();
	}
	else if (Index == 13)
	{
		return URestrictedNavigationQueryFilter14::StaticClass();
	}
	else if (Index == 14)
	{
		return URestrictedNavigationQueryFilter15::StaticClass();
	}
	else if (Index == 15)
	{
		return URestrictedNavigationQueryFilter16::StaticClass();
	}
	else if (Index == 16)
	{
		return URestrictedNavigationQueryFilter17::StaticClass();
	}
	else if (Index == 17)
	{
		return URestrictedNavigationQueryFilter18::StaticClass();
	}
	else if (Index == 18)
	{
		return URestrictedNavigationQueryFilter19::StaticClass();
	}
	else if (Index == 19)
	{
		return URestrictedNavigationQueryFilter20::StaticClass();
	}
	else
	{
		return nullptr;
	}
}
