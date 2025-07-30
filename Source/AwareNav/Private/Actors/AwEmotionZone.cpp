#include "Actors/AwEmotionZone.h"

#include "NavModifierComponent.h"
#include "Components/BoxComponent.h"

#include "NavAreas/AwEmotionNavAreas.h"

AAwEmotionZone::AAwEmotionZone()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	constexpr int32 NumBoxes = 8;
	for (int32 i = 0; i < NumBoxes; ++i)
	{
		const FName BoxName = *FString::Printf(TEXT("Box%d"), i);
		UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(BoxName);
		Box->SetupAttachment(RootComponent);
		Box->SetCanEverAffectNavigation(true);
		Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Box->bNavigationRelevant = true;

		Boxes.Add(Box);
	}

	NavModifier = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));
}

void AAwEmotionZone::BeginPlay()
{
	Super::BeginPlay();
}

void AAwEmotionZone::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	UpdateEmotionZone();
}

void AAwEmotionZone::SetEmotionZoneParams(const TSubclassOf<UAwEmotionNavArea_Base>& InNavAreaClass, const float InInnerRadius, const float InOuterRadius)
{
	NavAreaClass = InNavAreaClass;
	InnerRadius = InInnerRadius;
	OuterRadius = InOuterRadius;
}

void AAwEmotionZone::UpdateEmotionZone()
{	
	constexpr int32 NumSides = 8;

	const FVector Center = GetActorLocation();

	TArray<FVector> Outers, Inners;

	for (int32 i = 0; i < NumSides; ++i)
	{
		const float AngleRad = FMath::DegreesToRadians(i * 360.f / NumSides);
		const FVector Dir = FVector(FMath::Cos(AngleRad), FMath::Sin(AngleRad), 0.f);
		Outers.Add(Center + Dir * OuterRadius);
		Inners.Add(Center + Dir * InnerRadius);
	}

	for (int32 i = 0; i < NumSides; ++i)
	{
		const FVector& A1 = Outers[i];
		const FVector& A2 = Outers[(i + 1) % NumSides];
		const FVector& B2 = Inners[(i + 1) % NumSides];
		const FVector& B1 = Inners[i];

		// Midpoints
		const FVector OuterMid = (A1 + A2) * 0.5f;
		const FVector InnerMid = (B1 + B2) * 0.5f;
		const FVector CenterPos = (OuterMid + InnerMid) * 0.5f;

		// Radial (inward direction)
		const FVector Radial = ((B1 + B2) * 0.5f - (A1 + A2) * 0.5f).GetSafeNormal();

		// Create rotation matrix (Right = Tangent, Up = Z, Forward = Radial)
		const FRotator Rotation = FRotationMatrix::MakeFromXZ(Radial, FVector::UpVector).Rotator();

		// Box size
		const float Width = (A2 - A1).Size();         // tangential
		const float Depth = (A1 - B1).Size();         // radial

		const FVector BoxExtent = FVector(Depth * 0.5f, Width * 0.5f, 500.0f); // X,Y,Z

		// Update the box
		UBoxComponent* Box = Boxes[i];
		Box->SetWorldLocation(CenterPos);
		Box->SetWorldRotation(Rotation);
		Box->SetBoxExtent(BoxExtent);
	}
	
	NavModifier->SetAreaClass(NavAreaClass);

	// TODO: Need to be a better solution for this
	const FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + FVector(0.01f, 0.f, 0.f));
	SetActorLocation(CurrentLocation);
}
