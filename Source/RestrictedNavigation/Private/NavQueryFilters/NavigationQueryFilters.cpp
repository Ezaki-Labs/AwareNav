#include "NavQueryFilters/NavigationQueryFilters.h"

#include "NavigationData.h"
#include "AIController.h"

#include "Enums/PermissionEnum.h"
#include "NavAreas/RestrictedAreaHelpers.h"
#include "Components/RestrictedNavigationComponent.h"

URestrictedNavigationQueryFilter_Base::URestrictedNavigationQueryFilter_Base()
{
	FNavigationFilterArea FilterAreaA;
    FilterAreaA.AreaClass = URestrictedNavArea_Low1::StaticClass();
    Areas.Add(FilterAreaA);
	
	FNavigationFilterArea FilterAreaB;
    FilterAreaB.AreaClass = URestrictedNavArea_Low2::StaticClass();
    Areas.Add(FilterAreaB);
	
	FNavigationFilterArea FilterAreaC;
    FilterAreaC.AreaClass = URestrictedNavArea_Mid1::StaticClass();
    Areas.Add(FilterAreaC);
	
	FNavigationFilterArea FilterAreaD;
    FilterAreaD.AreaClass = URestrictedNavArea_Mid2::StaticClass();
    Areas.Add(FilterAreaD);
	
	FNavigationFilterArea FilterAreaE;
    FilterAreaE.AreaClass = URestrictedNavArea_Mid3::StaticClass();
    Areas.Add(FilterAreaE);
	
	FNavigationFilterArea FilterAreaF;
    FilterAreaF.AreaClass = URestrictedNavArea_Mid4::StaticClass();
    Areas.Add(FilterAreaF);
	
	FNavigationFilterArea FilterAreaG;
    FilterAreaG.AreaClass = URestrictedNavArea_High1::StaticClass();
    Areas.Add(FilterAreaG);
	
	FNavigationFilterArea FilterAreaH;
    FilterAreaH.AreaClass = URestrictedNavArea_High2::StaticClass();
    Areas.Add(FilterAreaH);
}

void URestrictedNavigationQueryFilter_Base::InitializeFilter(const ANavigationData& NavData, const UObject* Querier, FNavigationQueryFilter& Filter) const
{
	// apply overrides
	for (int32 i = 0; i < Areas.Num(); i++)
	{
		const FNavigationFilterArea& AreaData = Areas[i];
		
		const int32 AreaId = NavData.GetAreaID(AreaData.AreaClass);
		if (AreaId == INDEX_NONE)
		{
			continue;
		}

		else if (auto AIController = Cast<AAIController>(Querier))
		{
			if (auto QuerierPawn = AIController->GetPawn())
			{
				if (auto RestrictedNavigationComponent = QuerierPawn->GetComponentByClass<URestrictedNavigationComponent>())
				{
					EPermissionLevel NavAreaPermissionLevel = GetPermissionLevelByNavArea(AreaData.AreaClass);
					uint8 PermissionLevels = RestrictedNavigationComponent->GetPermissionLevels();

					if (!(PermissionLevels & (uint8)NavAreaPermissionLevel))
					{
						Filter.SetExcludedArea(IntCastChecked<uint8>(AreaId));
						continue;
					}
				}
			}
		}

		if (AreaData.bIsExcluded)
		{
			Filter.SetExcludedArea(IntCastChecked<uint8>(AreaId));
		}
		else
		{
			if (AreaData.bOverrideTravelCost)
			{
				Filter.SetAreaCost(IntCastChecked<uint8>(AreaId), 15);
			}

			if (AreaData.bOverrideEnteringCost)
			{
				Filter.SetFixedAreaEnteringCost(IntCastChecked<uint8>(AreaId), 15);
			}
		}
	}

	// apply flags
	Filter.SetIncludeFlags(IncludeFlags.Packed);
	Filter.SetExcludeFlags(ExcludeFlags.Packed);
}
