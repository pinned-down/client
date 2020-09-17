#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IStompClient.h"
#include "IStompMessage.h"

#include "Core/PDCardActorManager.h"

#include "PDGameMode.generated.h"

class UUDIContext;

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

    UUDIContext* GetUDIContext() const;

    UFUNCTION(BlueprintPure)
    UPDEventManager* GetEventManager() const;

    UFUNCTION(BlueprintPure)
    UPDCardActorManager* GetCardActorManager() const;

    UFUNCTION(BlueprintPure)
    UPDGameplayTagsManager* GetGameplayTagsManager() const;

private:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UPDCardActorManager> CardActorManagerClass;

    FString WebSocketUrl;
    TSharedPtr<IStompClient> StompClient;

    UPROPERTY()
    UUDIContext* UDIContext;

    UPROPERTY()
    UPDEventManager* EventManager;

    UPROPERTY()
    UPDCardActorManager* CardActorManager;

    UPROPERTY()
    UPDGameplayTagsManager* GameplayTagsManager;

    void OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString);
    void OnConnectionError(const FString& Error);

    void OnMessage(const IStompMessage& Message);
    void OnError(const FString& Error);
    void OnClosed(const FString& Reason);
};
