#pragma once

#include "CoreMinimal.h"
#include "AwareNavSubsystem.h"
#include "GameFramework/Actor.h"

#include "Enums/AwEmotionType.h"

#include "AwEmotionAreaVolume.generated.h"

class UAwAgentEmotionProfileComponent;
class USphereComponent;
class AAwEmotionZone;
class UAwEmotionNavArea_Base;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorEnteredEmotionArea, AActor*, Agent, UAwAgentEmotionProfileComponent*, AgentEmotionProfileComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorLeftEmotionArea, AActor*, Agent, UAwAgentEmotionProfileComponent*, AgentEmotionProfileComponent);

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
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Emotions")
	FOnActorEnteredEmotionArea OnActorEntered;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Emotions")
	FOnActorLeftEmotionArea OnActorLeft;

	UPROPERTY()
	TObjectPtr<USphereComponent> Area = nullptr;

	bool bEmotionsSystemEnabled = false;

	float MidEffectRadius = 200.0f;
	float LowEffectRadius = 300.0f;
	float HighEffectRadius = 100.0f;

	float ReduceAmountPerInterval = 0.0f;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> HighEffectZoneActor = nullptr;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> DefaultZoneActor = nullptr;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> LowEffectZoneActor = nullptr;
	
	UPROPERTY()
	TMap<EAwEmotionIntensity, TObjectPtr<UChildActorComponent>> ZoneActorMap;

	UPROPERTY()
	TSet<UAwAgentEmotionProfileComponent*> AgentsInArea;

public:
	AAwEmotionAreaVolume();
	
	void SetAreaParams(const EAwEmotionType InEmotionType, const float InRadius);
	void EnableAreaReducing(const float ReduceIntervalInSeconds, const float ReduceAmount);

	void ForceLeaveArea(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent);

protected:	
	virtual void PostRegisterAllComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void UpdateZones();

	UFUNCTION()
	void ReduceArea();
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ActorEntered(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent);
	void ActorLeft(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
