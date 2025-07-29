#include "Actors/AwRestrictedAreaVolume.h"

#include "NavigationSystem.h"

#include "AwareNavSettings.h"
#include "Components/AwAgentPermissionProfileComponent.h"
#include "NavAreas/AwRestrictedNavAreas.h"

AAwRestrictedAreaVolume::AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AreaClass = UAwRestrictedNavArea_None::StaticClass();
	SetActorEnableCollision(ECollisionEnabled::QueryOnly);
}

void AAwRestrictedAreaVolume::BeginPlay()
{
    Super::BeginPlay();

    const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
    bPermissionSystemEnabled = Settings->bEnablePermissionSystem;
    if (bPermissionSystemEnabled)
    {
        OnActorBeginOverlap.AddDynamic(this, &AAwRestrictedAreaVolume::OnBeginOverlap);
        OnActorEndOverlap.AddDynamic(this, &AAwRestrictedAreaVolume::OnEndOverlap);
    }
}

void AAwRestrictedAreaVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent: AgentsInArea)
    {
        if (IsValid(AgentPermissionProfileComponent))
        {
            AgentPermissionProfileComponent->LeavePermissionVolume(this);
            OnActorLeft.Broadcast(AgentPermissionProfileComponent->GetOwner(), AgentPermissionProfileComponent);
        }
    }
    
    Super::EndPlay(EndPlayReason);
}

void AAwRestrictedAreaVolume::SetPermissionLevel(EAwPermissionLevel NewPermissionLevel)
{
    PermissionLevel = NewPermissionLevel;
    AreaClass = UAwRestrictedNavArea_Base::GetNavAreaByPermissionLevel(PermissionLevel);

    FNavigationSystem::UpdateActorAndComponentData(*this);
}

void AAwRestrictedAreaVolume::ForceLeaveArea(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent)
{
    AgentsInArea.Remove(AgentPermissionProfileComponent);
    OnActorEntered.Broadcast(AgentPermissionProfileComponent->GetOwner(), AgentPermissionProfileComponent);
}

void AAwRestrictedAreaVolume::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (IsValid(OtherActor))
    {
        if (UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent = OtherActor->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(AgentPermissionProfileComponent))
        {
            ActorEntered(AgentPermissionProfileComponent);
        }
    }
}

void AAwRestrictedAreaVolume::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (IsValid(OtherActor))
    {
        if (UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent = OtherActor->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(AgentPermissionProfileComponent))
        {
            ActorLeft(AgentPermissionProfileComponent);
        }
    }
}

void AAwRestrictedAreaVolume::ActorEntered(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent)
{
    if (!AgentsInArea.Contains(AgentPermissionProfileComponent))
    {
        AgentPermissionProfileComponent->EnterPermissionVolume(this);
        AgentsInArea.Add(AgentPermissionProfileComponent);
        OnActorEntered.Broadcast(AgentPermissionProfileComponent->GetOwner(), AgentPermissionProfileComponent);
    }
}

void AAwRestrictedAreaVolume::ActorLeft(UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent)
{
    if (AgentsInArea.Contains(AgentPermissionProfileComponent))
    {
        AgentPermissionProfileComponent->LeavePermissionVolume(this);
        AgentsInArea.Remove(AgentPermissionProfileComponent);
        OnActorLeft.Broadcast(AgentPermissionProfileComponent->GetOwner(), AgentPermissionProfileComponent);
    }
}

#if WITH_EDITOR
void AAwRestrictedAreaVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(AAwRestrictedAreaVolume, PermissionLevel))
    {
        AreaClass = UAwRestrictedNavArea_Base::GetNavAreaByPermissionLevel(PermissionLevel);
    }
}
#endif
