#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"

#include "RestrictedNavArea_Mid1.generated.h"

UCLASS( BlueprintType )
class RESTRICTEDNAVIGATION_API URestrictedNavArea_Mid1 : public UNavArea
{
	GENERATED_BODY()

public:
	URestrictedNavArea_Mid1()
    {
        DrawColor = FColor(135, 135, 0);
    }
};
