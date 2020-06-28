// Copyright Epic Games, Inc. All Rights Reserved.


#include "PinnedDownGameModeBase.h"

#include "StompModule.h"


void APinnedDownGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    FStompModule& StompModule = FStompModule::Get();
    StompClient = StompModule.CreateClient(TEXT("ws://localhost:8080/gs-guide-websocket"), TEXT(""));

    StompClient->OnConnected().AddUObject(this, &APinnedDownGameModeBase::OnConnected);
    StompClient->OnConnectionError().AddUObject(this, &APinnedDownGameModeBase::OnConnectionError);
    StompClient->OnError().AddUObject(this, &APinnedDownGameModeBase::OnError);

    StompClient->Connect();
}

void APinnedDownGameModeBase::OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString)
{
    UE_LOG(LogTemp, Log, TEXT("APinnedDownGameModeBase::OnConnected - ProtocolVersion: %s, SessionId: %s, ServerString: %s"), *ProtocolVersion, *SessionId, *ServerString);

    FStompSubscriptionEvent StompSubscriptionEvent = FStompSubscriptionEvent::CreateUObject(this, &APinnedDownGameModeBase::OnMessage);
    StompClient->Subscribe(TEXT("/topic/greetings"), StompSubscriptionEvent);

    StompClient->Send(TEXT("/app/hello"), TEXT("{\"name\": \"Nick\"}"));
}

void APinnedDownGameModeBase::OnConnectionError(const FString& Error)
{
    UE_LOG(LogTemp, Error, TEXT("APinnedDownGameModeBase::OnConnectionError - %s"), *Error);
}

void APinnedDownGameModeBase::OnMessage(const IStompMessage& Message)
{
    UE_LOG(LogTemp, Log, TEXT("APinnedDownGameModeBase::OnMessage - %s"), *Message.GetBodyAsString());
}

void APinnedDownGameModeBase::OnError(const FString& Error)
{
    UE_LOG(LogTemp, Error, TEXT("APinnedDownGameModeBase::OnError - %s"), *Error);
}
