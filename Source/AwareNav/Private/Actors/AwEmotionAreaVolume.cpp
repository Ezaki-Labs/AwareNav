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

	Area = CreateDefaultSubobject<USphereComponent>(TEXT("Area"));
	Area->SetupAttachment(RootComponent);
	Area->SetCanEverAffectNavigation(false);
	Area->bNavigationRelevant = false;
	Area->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Area->SetSphereRadius(Radius * 0.9f);	

	HighEffectZoneActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("HighEffectZoneActor"));
	HighEffectZoneActor->SetChildActorClass(AAwEmotionZone::StaticClass());
	HighEffectZoneActor->SetupAttachment(Root);
	ZoneActorMap.Add(EAwEmotionIntensity::High, HighEffectZoneActor);

	DefaultZoneActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("DefaultZoneActor"));
	DefaultZoneActor->SetChildActorClass(AAwEmotionZone::StaticClass());
	DefaultZoneActor->SetupAttachment(Root);
	ZoneActorMap.Add(EAwEmotionIntensity::Default, DefaultZoneActor);

	LowEffectZoneActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("LowEffectZoneActor"));
	LowEffectZoneActor->SetChildActorClass(AAwEmotionZone::StaticClass());
	LowEffectZoneActor->SetupAttachment(Root);
	ZoneActorMap.Add(EAwEmotionIntensity::Low, LowEffectZoneActor);
}

void AAwEmotionAreaVolume::BeginPlay()
{
	Super::BeginPlay();

	const UAwareNavSettings* Settings = GetDefault<UAwareNavSettings>();
	bEmotionsSystemEnabled = Settings->bEnableEmotionSystem;
	if (bEmotionsSystemEnabled)
	{
		Area->OnComponentBeginOverlap.AddDynamic(this, &AAwEmotionAreaVolume::OnBeginOverlap);
		Area->OnComponentEndOverlap.AddDynamic(this, &AAwEmotionAreaVolume::OnEndOverlap);
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

	LowEffectRadius = Radius;
	HighEffectRadius = Radius * 0.33f;
	MidEffectRadius = HighEffectRadius * 2.0f;
	
	Area->SetSphereRadius(Radius * 0.9f);
	
	const FEmotionNavAreaGroup EmotionNavAreaGroup = UAwEmotionNavArea_Base::GetNavAreaByEmotionType(EmotionType);

	if (AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::High]->GetChildActor()))
	{
		Zone->SetEmotionZoneParams(EmotionNavAreaGroup.HighCostArea, 0.0f, HighEffectRadius, Radius);
		Zone->UpdateEmotionZone();
	}

	if (AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::Default]->GetChildActor()))
	{
		Zone->SetEmotionZoneParams(EmotionNavAreaGroup.DefaultArea, HighEffectRadius, MidEffectRadius, Radius);
		Zone->UpdateEmotionZone();
	}

	if (AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::Low]->GetChildActor()))
	{
		Zone->SetEmotionZoneParams(EmotionNavAreaGroup.LowCostArea, MidEffectRadius, LowEffectRadius, Radius);
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
