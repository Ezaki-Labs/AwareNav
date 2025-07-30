#include "NavAreas/AwRestrictedNavAreas.h"

#include "NavAreas/NavArea_Default.h"

UClass* UAwRestrictedNavArea_Base::GetNavAreaByPermissionLevel(const EAwPermissionLevel PermissionLevel)
{
	switch (PermissionLevel)
	{
	case EAwPermissionLevel::None:
		return UAwRestrictedNavArea_None::StaticClass();
	case EAwPermissionLevel::PermissionLevel_Low1:
		return UAwRestrictedNavArea_Low1::StaticClass();
	case EAwPermissionLevel::PermissionLevel_Low2:
		return UAwRestrictedNavArea_Low2::StaticClass();
	case EAwPermissionLevel::PermissionLevel_Mid1:
		return UAwRestrictedNavArea_Mid1::StaticClass();
	case EAwPermissionLevel::PermissionLevel_Mid2:
		return UAwRestrictedNavArea_Mid2::StaticClass();
	case EAwPermissionLevel::PermissionLevel_Mid3:
		return UAwRestrictedNavArea_Mid3::StaticClass();
	case EAwPermissionLevel::PermissionLevel_Mid4:
		return UAwRestrictedNavArea_Mid4::StaticClass();
	case EAwPermissionLevel::PermissionLevel_High1:
		return UAwRestrictedNavArea_High1::StaticClass();
	case EAwPermissionLevel::PermissionLevel_High2:
		return UAwRestrictedNavArea_High2::StaticClass();
	default:
		return UNavArea_Default::StaticClass();
	}
}

EAwPermissionLevel UAwRestrictedNavArea_Base::GetPermissionLevelByNavArea(const UClass* NavArea)
{
    if (NavArea == UAwRestrictedNavArea_None::StaticClass())
    {
        return EAwPermissionLevel::None;
    }
    else if (NavArea == UAwRestrictedNavArea_Low1::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_Low1;
    }
    else if (NavArea == UAwRestrictedNavArea_Low2::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_Low2;
    }
    else if (NavArea == UAwRestrictedNavArea_Mid1::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_Mid1;
    }
    else if (NavArea == UAwRestrictedNavArea_Mid2::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_Mid2;
    }
    else if (NavArea == UAwRestrictedNavArea_Mid3::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_Mid3;
    }
    else if (NavArea == UAwRestrictedNavArea_Mid4::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_Mid4;
    }
    else if (NavArea == UAwRestrictedNavArea_High1::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_High1;
    }
    else if (NavArea == UAwRestrictedNavArea_High2::StaticClass())
    {
        return EAwPermissionLevel::PermissionLevel_High2;
    }
    else
    {
        return EAwPermissionLevel::None;
    }
}