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

	UPROPERTY()
	TArray<TObjectPtr<UBoxComponent>> Boxes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNavModifierComponent> NavModifier = nullptr;

public:
	AAwEmotionZone();

	void UpdateEmotionZone(const TSubclassOf<UAwEmotionNavArea_Base>& NavAreaClass, const float Radius, const float MaxRadius) const;

protected:
	virtual void BeginPlay() override;
};
