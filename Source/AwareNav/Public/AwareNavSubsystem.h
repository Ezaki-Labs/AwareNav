#pragma once

#include "CoreMinimal.h"
#include "Enums/AwEmotionType.h"
#include "Enums/AwPermissionLevel.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "AwareNavSubsystem.generated.h"

class AAwRestrictedAreaVolume;

#pragma region Emotion Structs
USTRUCT(BlueprintType)
struct FEmotionAreaSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAwEmotionType EmotionType = EAwEmotionType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 400.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasLifeSpan = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSpan = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReducing = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReduceIntervalInSeconds = 3.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReduceAmountPerInterval = 20.0f;
};
#pragma endregion

UCLASS(ClassGroup=(AwareNav))
class AWARENAV_API UAwareNavSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
#pragma region Initialize
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
#pragma endregion

#pragma region Permissions
	// ----------- Agent with UAwAgentPermissionProfileComponent -----------

	UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions")
	void SetAgentPermissionGroupProfile(const AActor* Agent, const FName GroupID);

	// ----------- Restricted Area Volume -----------

	UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions")
	void SetAreaPermission(AAwRestrictedAreaVolume* Area, const EAwPermissionLevel NewPermission);
#pragma endregion

#pragma region Emotions	
	// ----------- Agent with UAwAgentPermissionProfileComponent -----------

	UFUNCTION(BlueprintCallable, Category = "AwareNav|Emotions")
	void SetAgentEmotionGroupProfile(const AActor* Agent, const FName GroupID);
	
	UFUNCTION(BlueprintCallable, Category = "AwareNav|Emotions")
	void BoostEmotion(const AActor* Agent, const EAwEmotionType EmotionType, const float BoostMultiplier);
	
	UFUNCTION(BlueprintCallable, Category = "AwareNav|Emotions")
	void BoostEmotionWithTimer(const AActor* Agent, const EAwEmotionType EmotionType, const float BoostMultiplier, const float BoostTime);

	// ----------- Emotion Area Volume -----------
	
	UFUNCTION(BlueprintCallable, Category = "AwareNav|Emotions")
	void SpawnEmotionArea(const FEmotionAreaSpawnParams& SpawnParams);
#pragma endregion
};
