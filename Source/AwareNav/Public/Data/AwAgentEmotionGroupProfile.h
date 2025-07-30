#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Enums/AwEmotionType.h"

#include "AwAgentEmotionGroupProfile.generated.h"

USTRUCT(BlueprintType)
struct AWARENAV_API FAwAgentEmotionGroupProfile : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Represents the character's emotional resilience and ability to withstand fear.
	// Higher values reduce the effect of fear-based emotional zones.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 20, UIMin = 1, UIMax = 20), Category = "Emotion", BlueprintReadWrite, meta = (ToolTip = "Emotional resilience against fear. Higher value means less influence from fear zones."))
	int32 Courage = 10;

	// Represents the character’s psychological drive to seek safety and comfort.
	// Higher values make the character more attracted to safety-affiliated emotional zones.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 20, UIMin = 1, UIMax = 20), Category = "Emotion", BlueprintReadWrite, meta = (ToolTip = "Affinity for comfort and security. Higher value increases attraction to safe zones."))
	int32 ComfortSeeking = 10;

	// Represents the character's emotional memory depth and sensitivity to the past.
	// Higher values increase emotional response to haunting and nostalgia zones.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 20, UIMin = 1, UIMax = 20), Category = "Emotion", BlueprintReadWrite, meta = (ToolTip = "Emotional memory sensitivity. Affects how strongly the character responds to nostalgia and haunting zones."))
	int32 Memory = 10;
};
