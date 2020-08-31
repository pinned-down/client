#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IStompClient.h"
#include "IStompMessage.h"

#include "Core/PDCardActorManager.h"

#include "PDGameMode.generated.h"

class UPDAction;
class UPDEventManager;

UCLASS()
class PINNEDDOWN_API APDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    APDGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    void SendActionToServer(UPDAction* Action);

    UFUNCTION(BlueprintPure)
    UPDEventManager* GetEventManager() const;

    UFUNCTION(BlueprintPure)
    UPDCardActorManager* GetCardActorManager() const;

private:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UPDCardActorManager> CardActorManagerClass;

    TSharedPtr<IStompClient> StompClient;

    UPROPERTY()
    UPDEventManager* EventManager;

    UPROPERTY()
    UPDCardActorManager* CardActorManager;

    void OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString);
    void OnConnectionError(const FString& Error);

    void OnMessage(const IStompMessage& Message);
    void OnError(const FString& Error);
};
