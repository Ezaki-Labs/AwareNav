#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_None.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_None : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_None()
    {
        DrawColor = FColor::White;
    }
};
