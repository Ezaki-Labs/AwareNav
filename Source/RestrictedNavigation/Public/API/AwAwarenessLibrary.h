#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Enums/AwPermissionLevel.h"

#include "AwAwarenessLibrary.generated.h"

struct FAwAgentPermissionGroupProfile;
class AAwRestrictedAreaVolume;

UCLASS()
class AWARENAV_API UAwAwarenessLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// ----------- Agent with UAwAgentPermissionProfileComponent -----------

	UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions")
	static void SetAgentGroupProfile(const AActor* Agent, const FName GroupID);

	// ----------- Restricted Area Volume -----------

	UFUNCTION(BlueprintCallable, Category = "AwareNav|Permissions")
	static void SetAreaPermission(AAwRestrictedAreaVolume* Area, const EAwPermissionLevel NewPermission);
};
