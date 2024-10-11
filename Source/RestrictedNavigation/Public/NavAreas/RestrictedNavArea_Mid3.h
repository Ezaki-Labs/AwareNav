#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_Mid3.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_Mid3 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_Mid3()
    {
        DrawColor = FColor(215, 215, 0);
    }
};
