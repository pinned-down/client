#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IStompClient.h"
#include "IStompMessage.h"

#include "PDGameMode.generated.h"

class UPDEventManager;

UCLASS()
class PINNEDDOWN_API APDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    UFUNCTION(BlueprintPure)
    UPDEventManager* GetEventManager() const;

private:
    TSharedPtr<IStompClient> StompClient;

    UPROPERTY()
    UPDEventManager* EventManager;

    void OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString);
    void OnConnectionError(const FString& Error);

    void OnMessage(const IStompMessage& Message);
    void OnError(const FString& Error);
};
