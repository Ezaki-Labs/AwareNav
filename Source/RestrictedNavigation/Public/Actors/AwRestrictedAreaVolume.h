#pragma once

#include "CoreMinimal.h"
#include "NavModifierVolume.h"

#include "Enums/AwPermissionLevel.h"

#include "AwRestrictedAreaVolume.generated.h"

UCLASS(BlueprintType)
class AWARENAV_API AAwRestrictedAreaVolume : public ANavModifierVolume
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAwPermissionLevel PermissionLevel = EAwPermissionLevel::None;

public:
	AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer);

	void SetPermissionLevel(EAwPermissionLevel NewPermissionLevel);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
