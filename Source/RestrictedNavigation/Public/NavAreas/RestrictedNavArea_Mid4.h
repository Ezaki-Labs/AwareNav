#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_Mid4.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_Mid4 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_Mid4()
    {
        DrawColor = FColor(255, 255, 0);
    }
};
