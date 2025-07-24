#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enums/AwEmotionType.h"

#include "AwEmotionAreaVolume.generated.h"

class AAwEmotionZone;
class UAwEmotionNavArea_Base;

UENUM(BlueprintType)
enum class EAwEmotionIntensity : uint8
{
	Default				UMETA(DisplayName = "Default"),
	Low					UMETA(DisplayName = "Low"),
	High				UMETA(DisplayName = "High"),
};

UCLASS(Blueprintable, BlueprintType)
class AWARENAV_API AAwEmotionAreaVolume : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AwareNav|Emotions")
	EAwEmotionType EmotionType = EAwEmotionType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin=0.0), Category = "AwareNav|Emotions")
	float DefaultRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin=0.0), Category = "AwareNav|Emotions")
	float LowEffectRadius = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin=0.0), Category = "AwareNav|Emotions")
	float HighEffectRadius = 300.0f;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> HighEffectZoneActor = nullptr;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> DefaultZoneActor = nullptr;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> LowEffectZoneActor = nullptr;
	
	UPROPERTY()
	TMap<EAwEmotionIntensity, TObjectPtr<UChildActorComponent>> ZoneActorMap;

public:
	AAwEmotionAreaVolume();
	AAwEmotionAreaVolume(const EAwEmotionType InEmotionType, const float InDefaultRadius, const float InLowEffectRadius = 0.0f, const float InHighEffectRadius = 0.0f);

protected:	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	void UpdateChildZones();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
