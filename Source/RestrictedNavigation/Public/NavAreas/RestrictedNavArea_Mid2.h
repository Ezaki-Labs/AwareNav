#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_Mid2.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_Mid2 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_Mid2()
    {
        DrawColor = FColor(175, 175, 0);
    }
};
