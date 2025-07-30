#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "Enums/AwEmotionType.h"

#include "AwEmotionNavAreas.generated.h"

UCLASS( Abstract )
class AWARENAV_API UAwEmotionNavArea_Base : public UNavArea
{
	GENERATED_BODY()

public:
	static EAwEmotionType GetEmotionTypeByNavArea(const UClass* EmotionType);
	static UClass* GetNavAreaByEmotionType(const EAwEmotionType EmotionType);
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_Fear : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_Fear()
	{
		DefaultCost = 1.0f;
		FixedAreaEnteringCost = 0.1f;
		DrawColor = FColor(131, 65, 191);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_Haunting : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_Haunting()
	{
		DefaultCost = 1.0f;
		FixedAreaEnteringCost = 0.1f;
		DrawColor = FColor(93, 38, 173);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_Safety : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_Safety()
	{
		DefaultCost = 1.0f;
		FixedAreaEnteringCost = 0.0f;
		DrawColor = FColor(40, 161, 110);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_Nostalgia : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_Nostalgia()
	{
		DefaultCost = 1.0f;
		FixedAreaEnteringCost = 0.0f;
		DrawColor = FColor(44, 129, 163);
	}
};
