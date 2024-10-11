#pragma once

#include "NavAreas/NavArea_Default.h"

#include "RestrictedNavArea_None.h"
#include "RestrictedNavArea_Low1.h"
#include "RestrictedNavArea_Low2.h"
#include "RestrictedNavArea_Mid1.h"
#include "RestrictedNavArea_Mid2.h"
#include "RestrictedNavArea_Mid3.h"
#include "RestrictedNavArea_Mid4.h"
#include "RestrictedNavArea_High1.h"
#include "RestrictedNavArea_High2.h"

#include "Enums/PermissionEnum.h"

static UClass* GetNavAreaByPermissionLevel(EPermissionLevel PermissionLevel)
{
	switch (PermissionLevel)
	{
	case EPermissionLevel::None:
		return URestrictedNavArea_None::StaticClass();
	case EPermissionLevel::PermissionLevel_Low1:
		return URestrictedNavArea_Low1::StaticClass();
	case EPermissionLevel::PermissionLevel_Low2:
		return URestrictedNavArea_Low2::StaticClass();
	case EPermissionLevel::PermissionLevel_Mid1:
		return URestrictedNavArea_Mid1::StaticClass();
	case EPermissionLevel::PermissionLevel_Mid2:
		return URestrictedNavArea_Mid2::StaticClass();
	case EPermissionLevel::PermissionLevel_Mid3:
		return URestrictedNavArea_Mid3::StaticClass();
	case EPermissionLevel::PermissionLevel_Mid4:
		return URestrictedNavArea_Mid4::StaticClass();
	case EPermissionLevel::PermissionLevel_High1:
		return URestrictedNavArea_High1::StaticClass();
	case EPermissionLevel::PermissionLevel_High2:
		return URestrictedNavArea_High2::StaticClass();
	default:
		return UNavArea_Default::StaticClass();
	}
}

static EPermissionLevel GetPermissionLevelByNavArea(UClass* NavAreaClass)
{
    if (NavAreaClass == URestrictedNavArea_None::StaticClass())
    {
        return EPermissionLevel::None;
    }
    else if (NavAreaClass == URestrictedNavArea_Low1::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_Low1;
    }
    else if (NavAreaClass == URestrictedNavArea_Low2::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_Low2;
    }
    else if (NavAreaClass == URestrictedNavArea_Mid1::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_Mid1;
    }
    else if (NavAreaClass == URestrictedNavArea_Mid2::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_Mid2;
    }
    else if (NavAreaClass == URestrictedNavArea_Mid3::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_Mid3;
    }
    else if (NavAreaClass == URestrictedNavArea_Mid4::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_Mid4;
    }
    else if (NavAreaClass == URestrictedNavArea_High1::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_High1;
    }
    else if (NavAreaClass == URestrictedNavArea_High2::StaticClass())
    {
        return EPermissionLevel::PermissionLevel_High2;
    }
    else
    {
        return EPermissionLevel::None;
    }
}