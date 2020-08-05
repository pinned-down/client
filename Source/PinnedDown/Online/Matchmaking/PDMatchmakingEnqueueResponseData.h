#pragma once

#include "CoreMinimal.h"

#include "PDMatchmakingEnqueueResponseData.generated.h"

USTRUCT()
struct PINNEDDOWN_API FPDMatchmakingEnqueueResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FString PlayerId;

    UPROPERTY()
    FString Status;
};
