#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "Enums/AwPermissionLevel.h"

#include "AwRestrictedNavAreas.generated.h"

class UAwRestrictedNavArea_None;

UCLASS( Abstract )
class AWARENAV_API UAwRestrictedNavArea_Base : public UNavArea
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Base()
	{
		DefaultCost = 0.0f;
	}
	
	static UClass* GetNavAreaByPermissionLevel(const EAwPermissionLevel PermissionLevel);
	static EAwPermissionLevel GetPermissionLevelByNavArea(const UClass* NavArea);
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_None : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_None()
    {
        DrawColor = FColor::Green;
    }
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Low1 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Low1()
	{
		DrawColor = FColor(156, 176, 113);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Low2 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Low2()
	{
		DrawColor = FColor(116, 153, 35);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid1 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid1()
	{
		DrawColor = FColor(201, 196, 157);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid2 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid2()
	{
		DrawColor = FColor(163, 154, 85);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid3 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid3()
	{
		DrawColor = FColor(115, 105, 31);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid4 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid4()
	{
		DrawColor = FColor(84, 75, 5);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_High1 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_High1()
	{
		DrawColor = FColor(143, 99, 66);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_High2 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_High2()
	{
		DrawColor = FColor(97, 49, 13);
	}
};
