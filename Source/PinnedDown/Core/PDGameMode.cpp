#include "PDGameMode.h"

#include "JsonObjectConverter.h"
#include "StompModule.h"
#include "Kismet/GameplayStatics.h"

#include "Core/PDLog.h"
#include "Core/PDGameInstance.h"
#include "Core/PDGameplayTagsManager.h"
#include "Events/PDAction.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDJoinGameAction.h"
#include "Events/EventData/PDLeaveGameAction.h"
#include "Online/Auth/PDAuthService.h"

APDGameMode::APDGameMode(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    CardActorManagerClass = UPDCardActorManager::StaticClass();
}

void APDGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    // Setup game.
    EventManager = NewObject<UPDEventManager>(this);

    CardActorManager = NewObject<UPDCardActorManager>(this, CardActorManagerClass);
    CardActorManager->Init(EventManager);

    GameplayTagsManager = NewObject<UPDGameplayTagsManager>(this);
    GameplayTagsManager->Init(EventManager);

    // Connect to server.
    FString ServerEndpoint = UGameplayStatics::ParseOption(Options, TEXT("server"));

    if (ServerEndpoint.IsEmpty())
    {
        UE_LOG(LogPD, Error, TEXT("No server endpoint specified."));
        return;
    }

    WebSocketUrl = TEXT("ws://") + ServerEndpoint + TEXT("/pinned-down");

    FStompModule& StompModule = FStompModule::Get();
    StompClient = StompModule.CreateClient(WebSocketUrl);

    StompClient->OnConnected().AddUObject(this, &APDGameMode::OnConnected);
    StompClient->OnConnectionError().AddUObject(this, &APDGameMode::OnConnectionError);
    StompClient->OnError().AddUObject(this, &APDGameMode::OnError);
    StompClient->OnClosed().AddUObject(this, &APDGameMode::OnClosed);

    StompClient->Connect();
}

void APDGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (StompClient != nullptr)
    {
        UE_LOG(LogPD, Log, TEXT("Disconnecting from %s ..."), *WebSocketUrl);

        // Send leave message.
        UPDGameInstance* GameInstance = GetGameInstance<UPDGameInstance>();
        UPDAuthService* AuthService = GameInstance->GetAuthService();
        UPDLeaveGameAction* LeaveAction = NewObject<UPDLeaveGameAction>(this);
        LeaveAction->PlayerId = AuthService->GetPlayerId();

        SendActionToServer(LeaveAction);

        StompClient->Disconnect();
    }
}

void APDGameMode::SendActionToServer(UPDAction* Action)
{
    FString Endpoint = TEXT("/game") + Action->Endpoint;

    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(Action->GetClass(), Action, JsonString, 0, 0);

    StompClient->Send(Endpoint, JsonString);
}

UPDEventManager* APDGameMode::GetEventManager() const
{
    return EventManager;
}

UPDCardActorManager* APDGameMode::GetCardActorManager() const
{
    return CardActorManager;
}

UPDGameplayTagsManager* APDGameMode::GetGameplayTagsManager() const
{
    return GameplayTagsManager;
}

void APDGameMode::OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString)
{
    UE_LOG(LogPD, Log, TEXT("APDGameMode::OnConnected - ProtocolVersion: %s, SessionId: %s, ServerString: %s"), *ProtocolVersion, *SessionId, *ServerString);

    // Subscribe for messages.
    FStompSubscriptionEvent StompSubscriptionEvent = FStompSubscriptionEvent::CreateUObject(this, &APDGameMode::OnMessage);
    StompClient->Subscribe(TEXT("/topic/events"), StompSubscriptionEvent);

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

    // TODO(np): Handle missing handshake response.
    UPDJoinGameAction* JoinAction = NewObject<UPDJoinGameAction>(this);
    JoinAction->PlayerId = AuthService->GetPlayerId();

    SendActionToServer(JoinAction);
}

void APDGameMode::OnConnectionError(const FString& Error)
{
    // TODO(np): Set error message and return to main menu.
    UE_LOG(LogPD, Error, TEXT("APDGameMode::OnConnectionError - %s"), *Error);
}

void APDGameMode::OnMessage(const IStompMessage& Message)
{
    UE_LOG(LogPD, Log, TEXT("APDGameMode::OnMessage - %s"), *Message.GetBodyAsString());

    // Deserialize message.
    TSharedPtr<FJsonObject> MessageJsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message.GetBodyAsString());
    FJsonSerializer::Deserialize(Reader, MessageJsonObject);

    FString MessageType = MessageJsonObject->GetStringField(TEXT("messageType"));
    TSharedPtr<FJsonObject> MessageData = MessageJsonObject->GetObjectField(TEXT("messageData"));

    // Get message type.
    int32 LastIndex;
    MessageType.FindLastChar('.', LastIndex);

    MessageType = MessageType.Mid(LastIndex + 1);
    MessageType = TEXT("PD") + MessageType;

    // Create message data object.
    UObject* ClassPackage = ANY_PACKAGE;

    UClass* MessageClass = FindObject<UClass>(ClassPackage, *MessageType);

    if (!MessageClass)
    {
        if (UObjectRedirector* RenamedClassRedirector = FindObject<UObjectRedirector>(ClassPackage, *MessageType))
        {
            MessageClass = CastChecked<UClass>(RenamedClassRedirector->DestinationObject);
        }
    }

    if (!MessageClass)
    {
        UE_LOG(LogPD, Error, TEXT("APDGameMode::OnMessage - Unknown MessageClass: %s"), *MessageType);
        return;
    }

    UObject* Obj = NewObject<UObject>(this, MessageClass);
    FJsonObjectConverter::JsonObjectToUStruct(MessageData.ToSharedRef(), MessageClass, Obj);

    // Raise event.
    EventManager->RaiseEvent(MessageType, Obj);
}

void APDGameMode::OnError(const FString& Error)
{
    // TODO(np): Set error message and return to main menu.
    UE_LOG(LogPD, Error, TEXT("APDGameMode::OnError - %s"), *Error);
}

void APDGameMode::OnClosed(const FString& Reason)
{
    UE_LOG(LogPD, Log, TEXT("APDGameMode::OnClosed - %s"), *Reason);
}
