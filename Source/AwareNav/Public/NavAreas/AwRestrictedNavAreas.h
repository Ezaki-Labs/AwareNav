#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "Enums/AwPermissionLevel.h"

#include "AwRestrictedNavAreas.generated.h"

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
	static EAwPermissionLevel GetPermissionLevelByNavArea(const UClass* NavAreaClass);
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_None : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_None()
    {
        DrawColor = FColor(80, 80, 255);
    }
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Low1 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Low1()
	{
		DrawColor = FColor(90, 90, 90);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Low2 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Low2()
	{
		DrawColor = FColor(120, 120, 120);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid1 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid1()
	{
		DrawColor = FColor(180, 180, 60);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid2 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid2()
	{
		DrawColor = FColor(210, 210, 100);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid3 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid3()
	{
		DrawColor = FColor(230, 230, 160);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_Mid4 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_Mid4()
	{
		DrawColor = FColor(250, 250, 220);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_High1 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_High1()
	{
		DrawColor = FColor(255, 200, 100);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwRestrictedNavArea_High2 : public UAwRestrictedNavArea_Base
{
	GENERATED_BODY()

public:
	UAwRestrictedNavArea_High2()
	{
		DrawColor = FColor(255, 160, 50);
	}
};
