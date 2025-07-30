#include "Actors/AwEmotionAreaVolume.h"

#include "Components/SphereComponent.h"

#include "Actors/AwEmotionZone.h"
#include "Components/AwAgentEmotionProfileComponent.h"
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
	
	TriggerVolume->SetSphereRadius(FMath::Max(Radius * 1.7, 1.f));
	

	LowEffectZoneActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("LowEffectZoneActor"));
	LowEffectZoneActor->SetChildActorClass(AAwEmotionZone::StaticClass());
	LowEffectZoneActor->SetupAttachment(Root);
	ZoneActorMap.Add(EAwEmotionIntensity::Low, LowEffectZoneActor);
	
	DefaultEffectZoneActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("DefaultEffectZoneActor"));
	DefaultEffectZoneActor->SetChildActorClass(AAwEmotionZone::StaticClass());
	DefaultEffectZoneActor->SetupAttachment(Root);
	ZoneActorMap.Add(EAwEmotionIntensity::Default, DefaultEffectZoneActor);
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

	DefaultEffectRadius = Radius;
	LowEffectRadius = Radius * 2.0f;
	
	TriggerVolume->SetSphereRadius(FMath::Max(Radius * 1.7, 1.f));
	
	const FEmotionNavAreaGroup EmotionNavAreaGroup = UAwEmotionNavArea_Base::GetNavAreaGroupByEmotionType(EmotionType);

	if (AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::Default]->GetChildActor()))
	{
		Zone->SetEmotionZoneParams(EmotionNavAreaGroup.DefaultArea, 0.0f, DefaultEffectRadius);
		Zone->UpdateEmotionZone();
	}

	if (AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::Low]->GetChildActor()))
	{
		Zone->SetEmotionZoneParams(EmotionNavAreaGroup.LowEffectArea, DefaultEffectRadius, LowEffectRadius);
		Zone->UpdateEmotionZone();
	}
}

#if WITH_EDITOR
void AAwEmotionAreaVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, EmotionType) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, Radius))
	{
		UpdateZones();
	}
}
#endif
