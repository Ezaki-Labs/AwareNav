#pragma once

#include "CoreMinimal.h"
#include "AwareNavSettings.h"
#include "NavAreas/NavArea.h"

#include "Enums/AwEmotionType.h"

#include "AwEmotionNavAreas.generated.h"

class UAwEmotionNavArea_Base;

USTRUCT(BlueprintType)
struct FEmotionNavAreaGroup
{
	GENERATED_BODY()

	FEmotionNavAreaGroup() {}
	FEmotionNavAreaGroup(const TSubclassOf<UAwEmotionNavArea_Base>& InDefaultArea, const TSubclassOf<UAwEmotionNavArea_Base>& InLowCostArea, const TSubclassOf<UAwEmotionNavArea_Base>& InHighCostArea)
		: DefaultArea(InDefaultArea)
		, LowCostArea(InLowCostArea)
		, HighCostArea(InHighCostArea)
	{}

	TSubclassOf<UAwEmotionNavArea_Base> DefaultArea;
	TSubclassOf<UAwEmotionNavArea_Base> LowCostArea;
	TSubclassOf<UAwEmotionNavArea_Base> HighCostArea;
};

UCLASS( Abstract )
class AWARENAV_API UAwEmotionNavArea_Base : public UNavArea
{
	GENERATED_BODY()

public:
	static FEmotionNavAreaGroup GetNavAreaGroupByEmotionType(const EAwEmotionType EmotionType);
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_FearDefault : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_FearDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->FearCost.DefaultCost;
		DrawColor = FColor(150, 60, 180);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_FearLow : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_FearLow()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->FearCost.LowCost;
		DrawColor = FColor(80, 40, 130);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_FearHigh : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_FearHigh()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->FearCost.HighCost;
		DrawColor = FColor(220, 60, 240);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_SafetyDefault : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_SafetyDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->SafetyCost.DefaultCost;
		DrawColor = FColor(60, 150, 120);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_SafetyLow : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_SafetyLow()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->SafetyCost.LowCost;
		DrawColor = FColor(40, 80, 80);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_SafetyHigh : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_SafetyHigh()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->SafetyCost.HighCost;
		DrawColor = FColor(80, 220, 160);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_NostalgiaDefault : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_NostalgiaDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->NostalgiaCost.DefaultCost;
		DrawColor = FColor(160, 100, 60);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_NostalgiaLow : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_NostalgiaLow()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->NostalgiaCost.LowCost;
		DrawColor = FColor(100, 60, 40);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_NostalgiaHigh : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_NostalgiaHigh()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->NostalgiaCost.HighCost;
		DrawColor = FColor(240, 160, 80);
	}
};
