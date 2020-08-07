#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IStompClient.h"
#include "IStompMessage.h"

#include "PDGameMode.generated.h"

UCLASS()
class PINNEDDOWN_API APDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
    TSharedPtr<IStompClient> StompClient;

    void OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString);
    void OnConnectionError(const FString& Error);

    void OnMessage(const IStompMessage& Message);
    void OnError(const FString& Error);
};
