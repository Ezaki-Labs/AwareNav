#include "Actors/AwRestrictedAreaVolume.h"

#include "NavAreas/AwRestrictedNavAreas.h"

AAwRestrictedAreaVolume::AAwRestrictedAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AreaClass = UAwRestrictedNavArea_None::StaticClass();
}

#if WITH_EDITOR
void AAwRestrictedAreaVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    // Check if the property that changed matches the one you're interested in
    if (PropertyName == GET_MEMBER_NAME_CHECKED(AAwRestrictedAreaVolume, PermissionLevel))
    {
        AreaClass = UAwRestrictedNavArea_Base::GetNavAreaByPermissionLevel(PermissionLevel);
    }
}
#endif
