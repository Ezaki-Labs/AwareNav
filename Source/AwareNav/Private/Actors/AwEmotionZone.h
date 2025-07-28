#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AwEmotionZone.generated.h"

class UBoxComponent;
class UAwEmotionNavArea_Base;
class UNavModifierComponent;

UCLASS()
class AWARENAV_API AAwEmotionZone : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNavModifierComponent> NavModifier = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UBoxComponent>> Boxes;

	UPROPERTY()
	TSubclassOf<UAwEmotionNavArea_Base> NavAreaClass = nullptr;

	float InnerRadius = 0.0f;
	float OuterRadius = 0.0f;
	float MaxRadius = 0.0f;

public:
	AAwEmotionZone();

	void SetEmotionZoneParams(const TSubclassOf<UAwEmotionNavArea_Base>& InNavAreaClass, const float InInnerRadius, const float InOuterRadius, const float InMaxRadius);
	void UpdateEmotionZone();

protected:
	virtual void BeginPlay() override;
	virtual void PostRegisterAllComponents() override;
};
