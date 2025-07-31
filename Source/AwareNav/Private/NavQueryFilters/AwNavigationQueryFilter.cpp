#include "NavQueryFilters/AwNavigationQueryFilter.h"

#include "NavigationData.h"
#include "AIController.h"

#include "AwareNavSettings.h"
#include "Enums/AwPermissionLevel.h"
#include "NavAreas/AwEmotionNavAreas.h"
#include "NavAreas/AwRestrictedNavAreas.h"
#include "Components/AwAgentPermissionProfileComponent.h"
#include "Components/AwAgentEmotionProfileComponent.h"

UAwNavigationQueryFilter::UAwNavigationQueryFilter()
{
	// Restricted Nav areas
	FNavigationFilterArea FilterArea_Low1;
	FilterArea_Low1.AreaClass = UAwRestrictedNavArea_Low1::StaticClass();
	Areas.Add(FilterArea_Low1);
	
	FNavigationFilterArea FilterArea_Low2;
	FilterArea_Low2.AreaClass = UAwRestrictedNavArea_Low2::StaticClass();
	Areas.Add(FilterArea_Low2);
		
	
	FNavigationFilterArea FilterArea_Mid1;
	FilterArea_Mid1.AreaClass = UAwRestrictedNavArea_Mid1::StaticClass();
	Areas.Add(FilterArea_Mid1);
	
	FNavigationFilterArea FilterArea_Mid2;
	FilterArea_Mid2.AreaClass = UAwRestrictedNavArea_Mid2::StaticClass();
	Areas.Add(FilterArea_Mid2);
	
	FNavigationFilterArea FilterArea_Mid3;
	FilterArea_Mid3.AreaClass = UAwRestrictedNavArea_Mid3::StaticClass();
	Areas.Add(FilterArea_Mid3);
	
	FNavigationFilterArea FilterArea_Mid4;
	FilterArea_Mid4.AreaClass = UAwRestrictedNavArea_Mid4::StaticClass();
	Areas.Add(FilterArea_Mid4);
		
	
	FNavigationFilterArea FilterArea_High1;
	FilterArea_High1.AreaClass = UAwRestrictedNavArea_High1::StaticClass();
	Areas.Add(FilterArea_High1);
	
	FNavigationFilterArea FilterArea_High2;
	FilterArea_High2.AreaClass = UAwRestrictedNavArea_High2::StaticClass();
	Areas.Add(FilterArea_High2);


	// Emotional Nav areas
	FNavigationFilterArea FilterArea_Fear;
	FilterArea_Fear.AreaClass = UAwEmotionNavArea_Fear::StaticClass();
	Areas.Add(FilterArea_Fear);
	
	FNavigationFilterArea FilterArea_Haunting;
	FilterArea_Haunting.AreaClass = UAwEmotionNavArea_Haunting::StaticClass();
	Areas.Add(FilterArea_Haunting);
	
	FNavigationFilterArea FilterArea_Safety;
	FilterArea_Safety.AreaClass = UAwEmotionNavArea_Safety::StaticClass();
	Areas.Add(FilterArea_Safety);
	
	FNavigationFilterArea FilterArea_Nostalgia;
	FilterArea_Nostalgia.AreaClass = UAwEmotionNavArea_Nostalgia::StaticClass();
	Areas.Add(FilterArea_Nostalgia);
	
	bInstantiateForQuerier = true;
}

void UAwNavigationQueryFilter::InitializeFilter(const ANavigationData& NavData, const UObject* Querier,
	FNavigationQueryFilter& Filter) const
{
	const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
	const bool bPermissionSystemEnabled = Settings->bEnablePermissionSystem;
	const bool bEmotionSystemEnabled = Settings->bEnableEmotionSystem;
	
	// apply overrides
	for (int32 i = 0; i < Areas.Num(); i++)
	{
		const FNavigationFilterArea& AreaData = Areas[i];
		
		const int32 AreaId = NavData.GetAreaID(AreaData.AreaClass);
		if (AreaId == INDEX_NONE)
		{
			continue;
		}

		if (const auto AIController = Cast<AAIController>(Querier))
		{
			if (const auto QuerierPawn = AIController->GetPawn())
			{
				if (!AreaData.AreaClass)
				{
					continue;
				}
				if (bPermissionSystemEnabled && AreaData.AreaClass->IsChildOf(UAwRestrictedNavArea_Base::StaticClass()))
				{					
					if (const auto RestrictedNavigationComponent = QuerierPawn->FindComponentByClass<UAwAgentPermissionProfileComponent>())
					{
						EAwPermissionLevel NavAreaPermissionLevel = UAwRestrictedNavArea_Base::GetPermissionLevelByNavArea(AreaData.AreaClass);
						const uint8 PermissionLevels = RestrictedNavigationComponent->GetPermissionLevels();

						if (!(PermissionLevels & static_cast<uint8>(NavAreaPermissionLevel)))
						{
							Filter.SetExcludedArea(IntCastChecked<uint8>(AreaId));
						}
					}
				}
				else if (AreaData.AreaClass->IsChildOf(UAwEmotionNavArea_Base::StaticClass()))
				{
					const UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent = QuerierPawn->FindComponentByClass<UAwAgentEmotionProfileComponent>();
					if (!bEmotionSystemEnabled || !IsValid(AgentEmotionProfileComponent))
					{
						Filter.SetFixedAreaEnteringCost(IntCastChecked<uint8>(AreaId), 0.0f);
						Filter.SetAreaCost(IntCastChecked<uint8>(AreaId), 1.0f);
						continue;
					}
					
					const float NewCost = AgentEmotionProfileComponent->GetEmotionalAreaCosts().FindOrAdd(AreaData.AreaClass, 1.0f);
					Filter.SetAreaCost(IntCastChecked<uint8>(AreaId), NewCost);
				}
			}
		}
	}

	// apply flags
	Filter.SetIncludeFlags(IncludeFlags.Packed);
	Filter.SetExcludeFlags(ExcludeFlags.Packed);
}
