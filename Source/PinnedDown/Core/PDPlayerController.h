#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PDPlayerController.generated.h"

class UPDAction;
class UPDEventManager;
class UPDUIMode;

UCLASS()
class PINNEDDOWN_API APDPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure)
    bool IsLocalPlayer(int64 PlayerEntityId) const;

    UFUNCTION(BlueprintCallable)
    void ServerEndMainPhase();

private:
    UPROPERTY()
    UPDUIMode* UIMode;

    int64 LocalPlayerEntityId;

    UFUNCTION()
    void OnPlayerEntityCreated(const UObject* EventData);

    UFUNCTION()
    void OnCardClicked(APDCardActor* ClickedActor);

    void SendActionToServer(UPDAction* Action);
    void SetUIMode(UPDUIMode* NewUIMode);
};
