#include "Actors/RestrictedAreaVolume.h"

#include "NavAreas/RestrictedAreaHelpers.h"

ARestrictedAreaVolume::ARestrictedAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AreaClass = URestrictedNavArea_None::StaticClass();
}

#if WITH_EDITOR
void ARestrictedAreaVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    // Check if the property that changed matches the one you're interested in
    if (PropertyName == GET_MEMBER_NAME_CHECKED(ARestrictedAreaVolume, PermissionLevel))
    {
        AreaClass = GetNavAreaByPermissionLevel(PermissionLevel);
    }
}
#endif
