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

AAwEmotionAreaVolume::AAwEmotionAreaVolume(const EAwEmotionType InEmotionType, const float InDefaultRadius,
	const float InLowEffectRadius, const float InHighEffectRadius)
		: EmotionType(InEmotionType)
		, DefaultRadius(InDefaultRadius)
		, LowEffectRadius(InLowEffectRadius)
		, HighEffectRadius(InHighEffectRadius)
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

void AAwEmotionAreaVolume::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AAwEmotionAreaVolume::UpdateChildZones()
{	
	if (DefaultRadius < 0.0f)
	{
		DefaultRadius = 0.0f;
	}
	if (LowEffectRadius <= DefaultRadius)
	{
		LowEffectRadius = 0.0f;
	}
	if (HighEffectRadius < 0.0f && HighEffectRadius >= DefaultRadius)
	{
		HighEffectRadius = 0.0f;
	}
	
	const FEmotionNavAreaGroup EmotionNavAreaGroup = UAwEmotionNavArea_Base::GetNavAreaByEmotionType(EmotionType);

	if (const AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::High]->GetChildActor()))
	{
		Zone->UpdateEmotionZone(EmotionNavAreaGroup.HighCostArea, HighEffectRadius, LowEffectRadius);
	}

	if (const AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::Default]->GetChildActor()))
	{
		Zone->UpdateEmotionZone(EmotionNavAreaGroup.DefaultArea, DefaultRadius, LowEffectRadius);
	}

	if (const AAwEmotionZone* Zone = Cast<AAwEmotionZone>(ZoneActorMap[EAwEmotionIntensity::Low]->GetChildActor()))
	{
		Zone->UpdateEmotionZone(EmotionNavAreaGroup.LowCostArea, LowEffectRadius, LowEffectRadius);
	}
}

#if WITH_EDITOR
void AAwEmotionAreaVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (
		PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, EmotionType) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, DefaultRadius) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, LowEffectRadius) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AAwEmotionAreaVolume, HighEffectRadius))
	{
		UpdateChildZones();
	}
}
#endif
