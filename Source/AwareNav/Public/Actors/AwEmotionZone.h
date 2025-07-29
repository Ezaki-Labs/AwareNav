#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AwEmotionZone.generated.h"

class UBoxComponent;
class UAwEmotionNavArea_Base;
class UNavModifierComponent;

UCLASS(NotBlueprintable, HideDropdown)
class AWARENAV_API AAwEmotionZone : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY()
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
