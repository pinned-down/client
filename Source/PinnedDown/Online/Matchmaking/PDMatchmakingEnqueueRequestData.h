#pragma once

#include "CoreMinimal.h"

#include "PDMatchmakingEnqueueRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDMatchmakingEnqueueRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;

    UPROPERTY(BlueprintReadWrite)
    FString Version;

    UPROPERTY(BlueprintReadWrite)
    FString GameMode;

    UPROPERTY(BlueprintReadWrite)
    FString Region;
};
