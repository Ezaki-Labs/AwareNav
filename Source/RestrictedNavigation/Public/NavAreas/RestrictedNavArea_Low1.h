#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_Low1.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_Low1 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_Low1()
    {
        DrawColor = FColor(0, 135, 135);
    }
};
