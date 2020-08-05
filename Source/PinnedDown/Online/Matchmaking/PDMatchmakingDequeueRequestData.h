#pragma once

#include "CoreMinimal.h"

#include "PDMatchmakingDequeueRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDMatchmakingDequeueRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
