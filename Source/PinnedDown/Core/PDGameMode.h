#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IStompClient.h"
#include "IStompMessage.h"

#include "Core/PDCardActorManager.h"

#include "PDGameMode.generated.h"

class UPDAction;
class UPDEventManager;
class UPDGameplayTagsManager;

UCLASS()
class PINNEDDOWN_API APDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    APDGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void SendActionToServer(UPDAction* Action);

    UFUNCTION(BlueprintPure)
    UPDEventManager* GetEventManager() const;

    UFUNCTION(BlueprintPure)
    APDCardActorManager* GetCardActorManager() const;

    UFUNCTION(BlueprintPure)
    UPDGameplayTagsManager* GetGameplayTagsManager() const;

private:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<APDCardActorManager> CardActorManagerClass;

    FString WebSocketUrl;
    TSharedPtr<IStompClient> StompClient;

    UPROPERTY()
    UPDEventManager* EventManager;

    UPROPERTY()
    APDCardActorManager* CardActorManager;

    UPROPERTY()
    UPDGameplayTagsManager* GameplayTagsManager;

    FString Ticket;
    
    void OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString);
    void OnConnectionError(const FString& Error);

    void OnMessage(const IStompMessage& Message);
    void OnError(const FString& Error);
    void OnClosed(const FString& Reason);
};
