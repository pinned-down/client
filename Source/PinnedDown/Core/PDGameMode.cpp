#include "PDGameMode.h"

#include "StompModule.h"
#include "Kismet/GameplayStatics.h"

#include "Core/PDLog.h"
#include "Core/PDGameInstance.h"
#include "Online/Auth/PDAuthService.h"

void APDGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    FString ServerEndpoint = UGameplayStatics::ParseOption(Options, TEXT("server"));

    if (ServerEndpoint.IsEmpty())
    {
        UE_LOG(LogPD, Error, TEXT("No server endpoint specified."));
        return;
    }

    FString WebSocketUrl = TEXT("ws://") + ServerEndpoint + TEXT("/pinned-down");

    FStompModule& StompModule = FStompModule::Get();
    StompClient = StompModule.CreateClient(WebSocketUrl);

    StompClient->OnConnected().AddUObject(this, &APDGameMode::OnConnected);
    StompClient->OnConnectionError().AddUObject(this, &APDGameMode::OnConnectionError);
    StompClient->OnError().AddUObject(this, &APDGameMode::OnError);

    StompClient->Connect();
}

void APDGameMode::OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString)
{
    UE_LOG(LogPD, Log, TEXT("APDGameMode::OnConnected - ProtocolVersion: %s, SessionId: %s, ServerString: %s"), *ProtocolVersion, *SessionId, *ServerString);

    // Subscribe for messages.
    FStompSubscriptionEvent StompSubscriptionEvent = FStompSubscriptionEvent::CreateUObject(this, &APDGameMode::OnMessage);
    StompClient->Subscribe(TEXT("/topic/messages"), StompSubscriptionEvent);

    // Send join message.
    UPDGameInstance* GameInstance = GetGameInstance<UPDGameInstance>();

    if (!IsValid(GameInstance))
    {
        return;
    }

    UPDAuthService* AuthService = GameInstance->GetAuthService();

    if (!IsValid(AuthService))
    {
        return;
    }

    // TODO(np): Serialize from UObject.
    // TODO(np): Handle missing handshake response.
    StompClient->Send(TEXT("/app/join"), TEXT("{\"playerId\": \"") + AuthService->GetPlayerId() + TEXT("\"}"));
}

void APDGameMode::OnConnectionError(const FString& Error)
{
    // TODO(np): Set error message and return to main menu.
    UE_LOG(LogPD, Error, TEXT("APDGameMode::OnConnectionError - %s"), *Error);
}

void APDGameMode::OnMessage(const IStompMessage& Message)
{
    // TODO(np): Handle message.
    UE_LOG(LogPD, Log, TEXT("APDGameMode::OnMessage - %s"), *Message.GetBodyAsString());
}

void APDGameMode::OnError(const FString& Error)
{
    // TODO(np): Set error message and return to main menu.
    UE_LOG(LogPD, Error, TEXT("APDGameMode::OnError - %s"), *Error);
}
