#include "AwEmotionZone.h"

#include "NavModifierComponent.h"
#include "Components/BoxComponent.h"

#include "NavAreas/AwEmotionNavAreas.h"

AAwEmotionZone::AAwEmotionZone()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	constexpr int32 NumBoxes = 4;
	for (int32 i = 0; i < NumBoxes; ++i)
	{
		const FName BoxName = *FString::Printf(TEXT("Box%d"), i);
		UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(BoxName);
		Box->SetupAttachment(RootComponent);
		Box->SetCanEverAffectNavigation(true);
		Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		Boxes.Add(Box);
	}

	NavModifier = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));
}

void AAwEmotionZone::UpdateEmotionZone(const TSubclassOf<UAwEmotionNavArea_Base>& NavAreaClass, const float Radius, const float MaxRadius) const
{
	constexpr int32 NumBoxes = 4;

	constexpr float AngleStepDeg = 180.0f / NumBoxes;

	const float BoxDepth = Radius * 2 * FMath::Tan(PI / NumBoxes);
	const float ArcLength = 2 * PI * Radius / NumBoxes;
	const float BoxWidth = ArcLength * 0.9f;

	const float BoxHeight = MaxRadius - Radius + 200.0f;

	for (int32 i = 0; i < NumBoxes; ++i)
	{
		UBoxComponent* Box = Boxes[i];
		const float AngleDeg = i * AngleStepDeg;

		const FRotator Rotation = FRotator(0.f, AngleDeg, 0.f);

		Box->SetBoxExtent(FVector(BoxDepth, BoxWidth * 0.5f, BoxHeight * 0.5f));
		Box->SetRelativeRotation(Rotation);
	}
	
	NavModifier->SetAreaClass(NavAreaClass);

	// TODO
    //FNavigationSystem::UpdateComponentData(*NavModifier);
}

void AAwEmotionZone::BeginPlay()
{
	Super::BeginPlay();
}
