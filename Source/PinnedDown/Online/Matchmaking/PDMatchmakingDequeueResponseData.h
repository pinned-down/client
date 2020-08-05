#pragma once

#include "CoreMinimal.h"

#include "PDMatchmakingDequeueResponseData.generated.h"

USTRUCT()
struct PINNEDDOWN_API FPDMatchmakingDequeueResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FString DequeuedPlayerId;
};
