#include "NavQueryFilters/AwNavigationQueryFilter.h"

#include "NavigationData.h"
#include "AIController.h"

#include "Enums/AwPermissionLevel.h"
#include "NavAreas/AwEmotionalNavAreas.h"
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
	FNavigationFilterArea FilterArea_FearLow;
	FilterArea_FearLow.AreaClass = UAwEmotionalNavArea_FearLow::StaticClass();
	Areas.Add(FilterArea_FearLow);
	
	FNavigationFilterArea FilterArea_FearMid;
	FilterArea_FearMid.AreaClass = UAwEmotionalNavArea_FearDefault::StaticClass();
	Areas.Add(FilterArea_FearMid);
	
	FNavigationFilterArea FilterArea_FearHigh;
	FilterArea_FearHigh.AreaClass = UAwEmotionalNavArea_FearHigh::StaticClass();
	Areas.Add(FilterArea_FearHigh);

	
	FNavigationFilterArea FilterArea_SafetyLow;
	FilterArea_SafetyLow.AreaClass = UAwEmotionalNavArea_SafetyLow::StaticClass();
	Areas.Add(FilterArea_SafetyLow);
	
	FNavigationFilterArea FilterArea_SafetyMid;
	FilterArea_SafetyMid.AreaClass = UAwEmotionalNavArea_SafetyDefault::StaticClass();
	Areas.Add(FilterArea_SafetyMid);
	
	FNavigationFilterArea FilterArea_SafetyHigh;
	FilterArea_SafetyHigh.AreaClass = UAwEmotionalNavArea_SafetyHigh::StaticClass();
	Areas.Add(FilterArea_SafetyHigh);

	
	FNavigationFilterArea FilterArea_NostalgiaLow;
	FilterArea_NostalgiaLow.AreaClass = UAwEmotionalNavArea_NostalgiaLow::StaticClass();
	Areas.Add(FilterArea_NostalgiaLow);
	
	FNavigationFilterArea FilterArea_NostalgiaMid;
	FilterArea_NostalgiaMid.AreaClass = UAwEmotionalNavArea_NostalgiaDefault::StaticClass();
	Areas.Add(FilterArea_NostalgiaMid);
	
	FNavigationFilterArea FilterArea_NostalgiaHigh;
	FilterArea_NostalgiaHigh.AreaClass = UAwEmotionalNavArea_NostalgiaHigh::StaticClass();
	Areas.Add(FilterArea_NostalgiaHigh);
	
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
					
					if (const auto RestrictedNavigationComponent = QuerierPawn->GetComponentByClass<UAwAgentPermissionProfileComponent>())
					{
						EAwPermissionLevel NavAreaPermissionLevel = UAwRestrictedNavArea_Base::GetPermissionLevelByNavArea(AreaData.AreaClass);
						const uint8 PermissionLevels = RestrictedNavigationComponent->GetPermissionLevels();

						if (!(PermissionLevels & static_cast<uint8>(NavAreaPermissionLevel)))
						{
							Filter.SetExcludedArea(IntCastChecked<uint8>(AreaId));
						}
					}
				}
				else if (AreaData.AreaClass->IsChildOf(UAwEmotionalNavArea_Base::StaticClass()))
				{
					if (!bEmotionSystemEnabled)
					{
						Filter.SetFixedAreaEnteringCost(IntCastChecked<uint8>(AreaId), 1.0f);
						Filter.SetAreaCost(IntCastChecked<uint8>(AreaId), 1.0f);
						continue;
					}
					
					if (const auto AgentEmotionProfileComponent = QuerierPawn->GetComponentByClass<UAwAgentEmotionProfileComponent>())
					{
						TSubclassOf<UAwEmotionalNavArea_Base> EmotionalNavArea_Base{AreaData.AreaClass};
					
						if (!AgentEmotionProfileComponent->GetEmotionalAreaCostMultipliers().Contains(EmotionalNavArea_Base))
						{
							continue;
						}

						const UNavArea* DefArea = (AreaData.AreaClass)->GetDefaultObject<UNavArea>();
						
						const float NewCost = AgentEmotionProfileComponent->GetEmotionalAreaCostMultipliers()[EmotionalNavArea_Base] * DefArea->DefaultCost;
						Filter.SetFixedAreaEnteringCost(IntCastChecked<uint8>(AreaId), NewCost);
						Filter.SetAreaCost(IntCastChecked<uint8>(AreaId), NewCost);
					}
				}
			}
		}
	}

	// apply flags
	Filter.SetIncludeFlags(IncludeFlags.Packed);
	Filter.SetExcludeFlags(ExcludeFlags.Packed);
}
