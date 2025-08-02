#include "Actors/AwRestrictedAreaVolume.h"

#include "NavigationSystem.h"
#include "Components/BoxComponent.h"

#include "AwareNavSettings.h"
#include "Components/AwAgentPermissionProfileComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "NavAreas/AwRestrictedNavAreas.h"

AAwRestrictedAreaVolume::AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    AreaClass = UAwRestrictedNavArea_None::StaticClass();

    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetUsingAbsoluteScale(true);
    TriggerVolume->SetupAttachment(RootComponent);
    
    TriggerVolume->SetCanEverAffectNavigation(false);
    TriggerVolume->bNavigationRelevant = false;
    
    TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolume->SetCollisionObjectType(ECC_WorldDynamic);
    TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerVolume->SetGenerateOverlapEvents(true);

#if WITH_EDITOR
    EditorOnlyBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorOnlyBillboard"));
    EditorOnlyBillboard->SetupAttachment(RootComponent);
    EditorOnlyBillboard->SetHiddenInGame(true);
    EditorOnlyBillboard->Sprite = LoadObject<UTexture2D>(nullptr, TEXT("/Engine/EditorResources/S_Actor.S_Actor"));
    EditorOnlyBillboard->SetRelativeLocation(FVector(0, 0, 100));

    EditorLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("EditorLabel"));
    EditorLabel->SetupAttachment(RootComponent);
    EditorLabel->SetText(EditorOnlyLabel);
    EditorLabel->SetHorizontalAlignment(EHTA_Center);
    EditorLabel->SetVerticalAlignment(EVRTA_TextCenter);
    EditorLabel->SetTextRenderColor(FColor::Black);
    EditorLabel->SetWorldSize(20.f);
    EditorLabel->SetYScale(3.0f);
    EditorLabel->AddRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    EditorLabel->SetVisibility(true);
    EditorLabel->SetHiddenInGame(true);
#endif
}

void AAwRestrictedAreaVolume::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    
    UpdateTriggerVolumeSize();
}

void AAwRestrictedAreaVolume::BeginPlay()
{
    Super::BeginPlay();

    const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
    bPermissionSystemEnabled = Settings->bEnablePermissionSystem;
    if (bPermissionSystemEnabled)
    {
        TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AAwRestrictedAreaVolume::OnBeginOverlap);
        TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AAwRestrictedAreaVolume::OnEndOverlap);
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

void AAwRestrictedAreaVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsValid(OtherActor))
    {
        if (UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent = OtherActor->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(AgentPermissionProfileComponent))
        {
            ActorEntered(AgentPermissionProfileComponent);
        }
    }
}

void AAwRestrictedAreaVolume::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (IsValid(OtherActor))
    {
        if (UAwAgentPermissionProfileComponent* AgentPermissionProfileComponent = OtherActor->FindComponentByClass<UAwAgentPermissionProfileComponent>(); IsValid(AgentPermissionProfileComponent))
        {
            ActorLeft(AgentPermissionProfileComponent);
        }
    }
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

void AAwRestrictedAreaVolume::UpdateTriggerVolumeSize() const
{
    const FVector OriginalExtent = GetBounds().BoxExtent;
    FVector ShrunkExtent = OriginalExtent - FVector(30.f);

    // Clamp to avoid negative extents
    ShrunkExtent.X = FMath::Max(ShrunkExtent.X, 1.f);
    ShrunkExtent.Y = FMath::Max(ShrunkExtent.Y, 1.f);
    ShrunkExtent.Z = FMath::Max(ShrunkExtent.Z, 1.f);

    TriggerVolume->SetBoxExtent(ShrunkExtent);
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
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(AAwRestrictedAreaVolume, EditorOnlyLabel))
    {
        EditorLabel->SetText(EditorOnlyLabel);
    }
}

void AAwRestrictedAreaVolume::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
    Super::PostEditChangeChainProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.Property)
    {
        const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
        if (PropertyName == GET_MEMBER_NAME_CHECKED(FBoxSphereBounds, BoxExtent))
        {    
            UpdateTriggerVolumeSize();
        }
    }
}

void AAwRestrictedAreaVolume::PostEditMove(bool bFinished)
{
    Super::PostEditMove(bFinished);
    
    UpdateTriggerVolumeSize();
}
#endif
