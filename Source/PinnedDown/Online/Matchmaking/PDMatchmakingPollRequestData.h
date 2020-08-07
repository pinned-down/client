#pragma once

#include "CoreMinimal.h"

#include "PDMatchmakingPollRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDMatchmakingPollRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
