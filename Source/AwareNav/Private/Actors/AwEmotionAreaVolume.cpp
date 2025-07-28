#include "Actors/AwEmotionAreaVolume.h"

#include "AwEmotionZone.h"
#include "NavAreas/AwEmotionNavAreas.h"

AAwEmotionAreaVolume::AAwEmotionAreaVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

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

void AAwEmotionAreaVolume::SetAreaParams(const EAwEmotionType InEmotionType, const float InRadius)
{
	EmotionType = InEmotionType;
	Radius = InRadius;
}

void AAwEmotionAreaVolume::EnableAreaReducing(const float InReduceSpeedPerMS)
{
	ReduceSpeedPerMS = InReduceSpeedPerMS;
	
	FTimerHandle LoopTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(LoopTimerHandle, this, &AAwEmotionAreaVolume::ReduceArea, 1.0f, true);
}

void AAwEmotionAreaVolume::ReduceArea()
{
	Radius -= ReduceSpeedPerMS;
	
	UpdateChildZones();
}

void AAwEmotionAreaVolume::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	UpdateChildZones();
}

void AAwEmotionAreaVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AAwEmotionAreaVolume::UpdateChildZones()
{
	if (Radius <= 0)
	{
		return;
	}

	LowEffectRadius = Radius;
	HighEffectRadius = Radius * 0.33f;
	MidEffectRadius = HighEffectRadius * 2.0f;
	
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
		UpdateChildZones();
	}
}
#endif
