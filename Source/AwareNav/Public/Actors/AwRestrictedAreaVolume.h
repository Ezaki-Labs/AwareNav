#pragma once

#include "CoreMinimal.h"
#include "NavModifierVolume.h"

#include "Enums/AwPermissionLevel.h"

#include "AwRestrictedAreaVolume.generated.h"

class UAwAgentPermissionProfileComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorEnteredRestrictedArea, AActor*, Agent, UAwAgentPermissionProfileComponent*, AgentPermissionProfileComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorLeftRestrictedArea, AActor*, Agent, UAwAgentPermissionProfileComponent*, AgentPermissionProfileComponent);

UCLASS(ClassGroup=(AwareNav), BlueprintType, Blueprintable)
class AWARENAV_API AAwRestrictedAreaVolume : public ANavModifierVolume
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="AwareNav|Permissions")
	EAwPermissionLevel PermissionLevel = EAwPermissionLevel::None;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions")
	FOnActorEnteredRestrictedArea OnActorEntered;
	
	UPROPERTY(BlueprintAssignable, Category="AwareNav|Permissions")
	FOnActorLeftRestrictedArea OnActorLeft;
	
	UPROPERTY()
	class UBoxComponent* TriggerVolume;

	bool bPermissionSystemEnabled = false;

	UPROPERTY()
	TSet<UAwAgentPermissionProfileComponent*> AgentsInArea;

public:
	AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer);

	void SetPermissionLevel(EAwPermissionLevel NewPermissionLevel);

	void ForceLeaveArea(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ActorEntered(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);
	void ActorLeft(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent);

	void UpdateTriggerVolumeSize() const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	virtual void PostEditMove(bool bFinished) override;
#endif
};
