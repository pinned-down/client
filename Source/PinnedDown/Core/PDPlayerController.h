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

    UFUNCTION(BlueprintCallable)
    void ServerAssignStarship(int64 AssignedStarship, int64 AssignedTo);

    UFUNCTION(BlueprintCallable)
    void ServerEndAssignmentPhase();

    UFUNCTION(BlueprintCallable)
    void ServerResolveFight(int64 EntityId);

private:
    UPROPERTY()
    UPDUIMode* UIMode;

    int64 LocalPlayerEntityId;

    UFUNCTION()
    void OnPlayerEntityCreated(const UObject* EventData);

    UFUNCTION()
    void OnTurnPhaseStarted(const UObject* EventData);

    UFUNCTION()
    void OnCardClicked(APDCardActor* ClickedActor);

    void SendActionToServer(UPDAction* Action);
    void SetUIMode(UPDUIMode* NewUIMode);
};
