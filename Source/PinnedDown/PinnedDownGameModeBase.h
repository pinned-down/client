// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IStompClient.h"
#include "IStompMessage.h"

#include "PinnedDownGameModeBase.generated.h"

UCLASS()
class PINNEDDOWN_API APinnedDownGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

private:
    TSharedPtr<IStompClient> StompClient;

    void OnConnected(const FString& ProtocolVersion, const FString& SessionId, const FString& ServerString);
    void OnConnectionError(const FString& Error);

    void OnMessage(const IStompMessage& Message);
    void OnError(const FString& Error);
};
