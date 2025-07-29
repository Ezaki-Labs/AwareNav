#pragma once

#include "CoreMinimal.h"
#include "NavModifierVolume.h"

#include "Enums/AwPermissionLevel.h"

#include "AwRestrictedAreaVolume.generated.h"

class UAwAgentPermissionProfileComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorEnteredRestrictedArea, AActor*, Agent, UAwAgentPermissionProfileComponent*, AgentPermissionProfileComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorLeftRestrictedArea, AActor*, Agent, UAwAgentPermissionProfileComponent*, AgentPermissionProfileComponent);

UCLASS(Blueprintable, BlueprintType)
class AWARENAV_API AAwRestrictedAreaVolume : public ANavModifierVolume
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="AwareNav|Permissions")
	EAwPermissionLevel PermissionLevel = EAwPermissionLevel::None;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions")
	FOnActorEnteredRestrictedArea OnActorEntered;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions")
	FOnActorLeftRestrictedArea OnActorLeft;

	bool bPermissionSystemEnabled = false;

	UPROPERTY()
	TSet<UAwAgentPermissionProfileComponent*> AgentsInArea;

public:
	AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer);

	void SetPermissionLevel(EAwPermissionLevel NewPermissionLevel);

	void ForceLeaveArea(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void ActorEntered(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);
	void ActorLeft(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
