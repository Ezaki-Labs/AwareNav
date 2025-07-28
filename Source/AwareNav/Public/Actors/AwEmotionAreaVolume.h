#pragma once

#include "CoreMinimal.h"
#include "AwareNavSubsystem.h"
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
	EAwEmotionType EmotionType = EAwEmotionType::Fear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin=0.0), Category = "AwareNav|Emotions")
	float Radius = 300.0f;

	float MidEffectRadius = 200.0f;
	float LowEffectRadius = 300.0f;
	float HighEffectRadius = 100.0f;

	float ReduceSpeedPerMS = 0.0f;

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
	
	void SetAreaParams(const EAwEmotionType InEmotionType, const float InRadius);
	void EnableAreaReducing(const float InReduceSpeedPerMS);

protected:	
	virtual void PostRegisterAllComponents() override;
	virtual void BeginPlay() override;
	
	void UpdateChildZones();

	UFUNCTION()
	void ReduceArea();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
