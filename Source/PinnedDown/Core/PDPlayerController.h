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

    UFUNCTION(BlueprintCallable)
    void ServerPlayEffect(const FString& EffectCardId, int64 TargetEntityId);

    UFUNCTION(BlueprintCallable)
    void ServerPlayStarship(const FString& StarshipCardId);

    virtual void NotifyOnError(const FString& ErrorCode, const FText& ErrorMessage);
    virtual void NotifyOnHintChanged(const FText& Hint);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnError"))
    void ReceiveOnError(const FString& ErrorCode, const FText& ErrorMessage);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHintChanged"))
    void ReceiveOnHintChanged(const FText& Hint);

private:
    UPROPERTY(EditDefaultsOnly)
    FName ErrorLocalizationTableId;

    UPROPERTY()
    UPDUIMode* UIMode;

    int64 LocalPlayerEntityId;

    TSet<FString> SentActionIds;

    UFUNCTION()
    void OnPlayerEntityCreated(const UObject* EventData);

    UFUNCTION()
    void OnTurnPhaseStarted(const UObject* EventData);

    UFUNCTION()
    void OnError(const UObject* EventData);

    UFUNCTION()
    void OnCardClicked(APDCardActor* ClickedActor);

    UFUNCTION()
    void OnHintChanged(const FText& Hint);

    void SendActionToServer(UPDAction* Action);
    void SetUIMode(UPDUIMode* NewUIMode);
};
