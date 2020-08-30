#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PDPlayerController.generated.h"

class UPDEventManager;

UCLASS()
class PINNEDDOWN_API APDPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure)
    bool IsLocalPlayer(int64 PlayerEntityId) const;

private:
    int64 LocalPlayerEntityId;

    UFUNCTION()
    void OnPlayerEntityCreated(const UObject* EventData);
};
