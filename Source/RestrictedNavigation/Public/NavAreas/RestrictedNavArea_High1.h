#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_High1.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_High1 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_High1()
    {
        DrawColor = FColor(135, 0, 0);
    }
};
