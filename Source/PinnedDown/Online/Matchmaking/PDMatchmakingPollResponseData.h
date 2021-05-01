#pragma once

#include "CoreMinimal.h"

#include "PDMatchmakingPollResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDMatchmakingPollResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FString Ticket;
    
    UPROPERTY(BlueprintReadOnly)
    FString ServerId;

    UPROPERTY(BlueprintReadOnly)
    FString IpV4Address;

    UPROPERTY(BlueprintReadOnly)
    int32 Port;

    UPROPERTY(BlueprintReadOnly)
    FString Status;
};
