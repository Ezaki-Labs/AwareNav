#include "Actors/AwEmotionAreaVolume.h"

#include "AwareNavSettings.h"
#include "AI/NavigationSystemBase.h"
#include "Components/SphereComponent.h"

#include "Components/AwAgentEmotionProfileComponent.h"
#include "Components/BillboardComponent.h"
#include "NavAreas/AwEmotionNavAreas.h"

AAwEmotionAreaVolume::AAwEmotionAreaVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	

	TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(Root);
	
	TriggerVolume->SetCanEverAffectNavigation(false);
	TriggerVolume->bNavigationRelevant = false;
	
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerVolume->SetGenerateOverlapEvents(true);
	
	TriggerVolume->SetSphereRadius(FMath::Max(Radius * EmotionTriggerZoneRadiusMultiplier, 1.f));
	
	
	NavZoneActor = CreateDefaultSubobject<USphereComponent>(TEXT("DefaultEffectZoneActor"));
	NavZoneActor->SetupAttachment(Root);
	NavZoneActor->SetCanEverAffectNavigation(true);
	NavZoneActor->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	NavZoneActor->bNavigationRelevant = true;
	NavZoneActor->bDynamicObstacle = true;

#if WITH_EDITOR
	EditorOnlyBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorOnlyBillboard"));
	EditorOnlyBillboard->SetupAttachment(RootComponent);
	EditorOnlyBillboard->SetHiddenInGame(true);
	EditorOnlyBillboard->Sprite = LoadObject<UTexture2D>(nullptr, TEXT("/Engine/EditorResources/S_Actor.S_Actor"));
	EditorOnlyBillboard->SetRelativeLocation(FVector(0, 0, 100));
#endif
}

AAwEmotionAreaVolume* AAwEmotionAreaVolume::SpawnEmotionArea(UWorld* World, const FEmotionAreaSpawnParams& SpawnParams)
{
	if (AAwEmotionAreaVolume* Spawned = World->SpawnActor<AAwEmotionAreaVolume>(SpawnParams.SpawnLocation, FRotator::ZeroRotator))
	{
		Spawned->SetAreaParams(SpawnParams.EmotionType, SpawnParams.Radius);
		if (SpawnParams.bHasLifeSpan)
		{
			Spawned->SetLifeSpan(SpawnParams.LifeSpan);
		}
		if (SpawnParams.bReducing)
		{
			Spawned->EnableAreaReducing(SpawnParams.ReduceIntervalInSeconds, SpawnParams.ReduceAmountPerInterval);
		}

		return Spawned;
	}

	return nullptr;
}

void AAwEmotionAreaVolume::BeginPlay()
{
	Super::BeginPlay();

	const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
	bEmotionsSystemEnabled = Settings->bEnableEmotionSystem;
	if (bEmotionsSystemEnabled)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AAwEmotionAreaVolume::OnBeginOverlap);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AAwEmotionAreaVolume::OnEndOverlap);
	}
}

void AAwEmotionAreaVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent: AgentsInArea)
	{
		if (IsValid(AgentEmotionProfileComponent))
		{
			AgentEmotionProfileComponent->LeaveEmotionVolume(this);
			OnActorLeft.Broadcast(AgentEmotionProfileComponent->GetOwner(), AgentEmotionProfileComponent);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void AAwEmotionAreaVolume::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	UpdateZones();
}

void AAwEmotionAreaVolume::SetAreaParams(const EAwEmotionType InEmotionType, const float InRadius)
{
	EmotionType = InEmotionType;
	Radius = InRadius;

	UpdateZones();
}

void AAwEmotionAreaVolume::EnableAreaReducing(const float ReduceIntervalInSeconds, const float ReduceAmount)
{
	if (bEmotionsSystemEnabled)
	{
		ReduceAmountPerInterval = ReduceAmount;
	
		FTimerHandle LoopTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(LoopTimerHandle, this, &AAwEmotionAreaVolume::ReduceArea, ReduceIntervalInSeconds, true);
	}
}

void AAwEmotionAreaVolume::ForceLeaveArea(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent)
{
	AgentsInArea.Remove(AgentEmotionProfileComponent);
	OnActorEntered.Broadcast(AgentEmotionProfileComponent->GetOwner(), AgentEmotionProfileComponent);
}

void AAwEmotionAreaVolume::ReduceArea()
{
	Radius -= ReduceAmountPerInterval;
	
	UpdateZones();
}

void AAwEmotionAreaVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent = OtherActor->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(AgentEmotionProfileComponent))
		{
			ActorEntered(AgentEmotionProfileComponent);
		}
	}
}

void AAwEmotionAreaVolume::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		if (UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent = OtherActor->FindComponentByClass<UAwAgentEmotionProfileComponent>(); IsValid(AgentEmotionProfileComponent))
		{
			ActorLeft(AgentEmotionProfileComponent);
		}
	}
}

void AAwEmotionAreaVolume::ActorEntered(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent)
{
	if (!AgentsInArea.Contains(AgentEmotionProfileComponent))
	{
		AgentEmotionProfileComponent->EnterEmotionVolume(this);
		AgentsInArea.Add(AgentEmotionProfileComponent);
		OnActorEntered.Broadcast(AgentEmotionProfileComponent->GetOwner(), AgentEmotionProfileComponent);
	}
}

void AAwEmotionAreaVolume::ActorLeft(UAwAgentEmotionProfileComponent* AgentEmotionProfileComponent)
{
	if (AgentsInArea.Contains(AgentEmotionProfileComponent))
	{
		AgentEmotionProfileComponent->LeaveEmotionVolume(this);
		AgentsInArea.Remove(AgentEmotionProfileComponent);
		OnActorLeft.Broadcast(AgentEmotionProfileComponent->GetOwner(), AgentEmotionProfileComponent);
	}
}

void AAwEmotionAreaVolume::UpdateZones()
{
	if (Radius <= 0)
	{
		return;
	}
	
	TriggerVolume->SetSphereRadius(FMath::Max(Radius * EmotionTriggerZoneRadiusMultiplier, 1.f));
	NavZoneActor->SetSphereRadius(Radius);
	
	NavZoneActor->SetAreaClassOverride(UAwEmotionNavArea_Base::GetNavAreaByEmotionType(EmotionType));
	
	FNavigationSystem::UpdateActorAndComponentData(*this);
}

#if WITH_EDITOR
void AAwEmotionAreaVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, Radius) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, EmotionType))
	{
		UpdateZones();
	}
}
#endif
