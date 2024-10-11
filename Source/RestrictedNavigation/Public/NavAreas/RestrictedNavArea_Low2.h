#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_Low2.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_Low2 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_Low2()
    {
        DrawColor = FColor(0, 255, 255);
    }
};
