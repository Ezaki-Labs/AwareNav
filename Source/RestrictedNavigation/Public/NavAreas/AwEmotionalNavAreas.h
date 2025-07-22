#pragma once

#include "CoreMinimal.h"
#include "AwareNavSettings.h"
#include "NavAreas/NavArea.h"

#include "AwEmotionalNavAreas.generated.h"

UCLASS( BlueprintType, Abstract )
class AWARENAV_API UAwEmotionalNavArea_Base : public UNavArea
{
	GENERATED_BODY()
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_FearLow : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_FearLow()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->FearCost.LowCost;
		DrawColor = FColor(80, 40, 130);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_FearDefault : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_FearDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->FearCost.DefaultCost;
		DrawColor = FColor(150, 60, 180);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_FearHigh : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_FearHigh()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->FearCost.HighCost;
		DrawColor = FColor(220, 60, 240);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_SafetyLow : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_SafetyLow()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->SafetyCost.LowCost;
		DrawColor = FColor(40, 80, 80);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_SafetyDefault : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_SafetyDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->SafetyCost.DefaultCost;
        DefaultCost = 0.5f;
		DrawColor = FColor(60, 150, 120);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_SafetyHigh : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_SafetyHigh()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->SafetyCost.HighCost;
        DefaultCost = 0.3f;
		DrawColor = FColor(80, 220, 160);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_NostalgiaLow : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_NostalgiaLow()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->NostalgiaCost.LowCost;
        DefaultCost = 1.0f;
		DrawColor = FColor(100, 60, 40);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_NostalgiaDefault : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_NostalgiaDefault()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->NostalgiaCost.DefaultCost;
        DefaultCost = 0.7f;
		DrawColor = FColor(160, 100, 60);
	}
};

UCLASS( BlueprintType )
class AWARENAV_API UAwEmotionalNavArea_NostalgiaHigh : public UAwEmotionalNavArea_Base
{
	GENERATED_BODY()

public:
	UAwEmotionalNavArea_NostalgiaHigh()
	{
		const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
		DefaultCost = Settings->NostalgiaCost.HighCost;
        DefaultCost = 0.5f;
		DrawColor = FColor(240, 160, 80);
	}
};
