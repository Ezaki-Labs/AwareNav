#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_High2.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_High2 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_High2()
    {
        DrawColor = FColor(255, 0, 0);
    }
};
