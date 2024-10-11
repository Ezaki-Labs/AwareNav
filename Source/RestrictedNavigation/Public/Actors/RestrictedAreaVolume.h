#pragma once

#include "CoreMinimal.h"
#include "NavModifierVolume.h"

#include "Enums/PermissionEnum.h"

#include "RestrictedAreaVolume.generated.h"

UCLASS(BlueprintType)
class RESTRICTEDNAVIGATION_API ARestrictedAreaVolume : public ANavModifierVolume
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "AAA_Identification", meta = (AllowPrivateAccess = "true"))
	EPermissionLevel PermissionLevel = EPermissionLevel::None;

public:
	ARestrictedAreaVolume(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
