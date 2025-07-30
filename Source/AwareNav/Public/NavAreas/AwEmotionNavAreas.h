#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "AwareNavSettings.h"
#include "Enums/AwEmotionType.h"

#include "AwEmotionNavAreas.generated.h"

class UAwEmotionNavArea_Base;

USTRUCT(BlueprintType)
struct FEmotionNavAreaGroup
{
	GENERATED_BODY()

	FEmotionNavAreaGroup() {}
	FEmotionNavAreaGroup(const TSubclassOf<UAwEmotionNavArea_Base>& InDefaultArea, const TSubclassOf<UAwEmotionNavArea_Base>& InLowEffectArea)
		: DefaultArea(InDefaultArea)
		, LowEffectArea(InLowEffectArea)
	{}

	TSubclassOf<UAwEmotionNavArea_Base> DefaultArea;
	TSubclassOf<UAwEmotionNavArea_Base> LowEffectArea;
};

UCLASS( Abstract )
class AWARENAV_API UAwEmotionNavArea_Base : public UNavArea
{
	GENERATED_BODY()

public:	
	EAwEmotionType EmotionType = EAwEmotionType::None;

	float GetAreaDynamicCost(const float CostMultiplier = 1.0f) const;
	
	static FEmotionNavAreaGroup GetNavAreaGroupByEmotionType(const EAwEmotionType EmotionType);

protected:
	float EmotionLowEffectDiff = 0.0f;
	bool bIsLowEffectArea = false;
	float DefaultEffectAreaCost = 0.0f;
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_FearDefault : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_FearDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultEffectAreaCost = Settings->FearCost;
		EmotionType = EAwEmotionType::Fear;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(92, 20, 87);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_FearLowEffect : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_FearLowEffect()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultEffectAreaCost = Settings->FearCost;
		EmotionType = EAwEmotionType::Fear;
		bIsLowEffectArea = true;
		EmotionLowEffectDiff = Settings->EmotionLowEffectDiff;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(166, 80, 160);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_HauntingDefault : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_HauntingDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultEffectAreaCost = Settings->HauntingCost;
		EmotionType = EAwEmotionType::Haunting;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(51, 38, 89);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_HauntingLowEffect : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_HauntingLowEffect()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultEffectAreaCost = Settings->HauntingCost;
		EmotionType = EAwEmotionType::Haunting;
		bIsLowEffectArea = true;
		EmotionLowEffectDiff = Settings->EmotionLowEffectDiff;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(131, 112, 186);
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
		DefaultEffectAreaCost = Settings->SafetyCost;
		EmotionType = EAwEmotionType::Safety;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(16, 54, 52);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_SafetyLowEffect : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_SafetyLowEffect()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultEffectAreaCost = Settings->SafetyCost;
		EmotionType = EAwEmotionType::Safety;
		bIsLowEffectArea = true;
		EmotionLowEffectDiff = Settings->EmotionLowEffectDiff;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(102, 173, 170);
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
		DefaultEffectAreaCost = Settings->NostalgiaCost;
		EmotionType = EAwEmotionType::Nostalgia;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(12, 38, 54);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionNavArea_NostalgiaLowEffect : public UAwEmotionNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionNavArea_NostalgiaLowEffect()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultEffectAreaCost = Settings->NostalgiaCost;
		EmotionType = EAwEmotionType::Nostalgia;
		bIsLowEffectArea = true;
		EmotionLowEffectDiff = Settings->EmotionLowEffectDiff;

		//DefaultCost = GetAreaDynamicCost();
		DrawColor = FColor(96, 138, 163);
	}
};
