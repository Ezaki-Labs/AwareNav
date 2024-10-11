#include "Components/RestrictedNavigationComponent.h"

#include "Data/NavigationPermissionsTemplate.h"

URestrictedNavigationComponent::URestrictedNavigationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URestrictedNavigationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FNavigationPermissionsTemplate* NavigationPermissionsTemplate = NavigationTemplate.GetRow<FNavigationPermissionsTemplate>(TEXT("Getting Data")))
	{
		PermissionLevels = NavigationPermissionsTemplate->PermissionLevels;
		NavQueryFilter = NavigationPermissionsTemplate->NavQueryFilter;
	}
}
