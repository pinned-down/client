#pragma once

#include "CoreMinimal.h"

#include "PDAuthLoginRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAuthLoginRequestData
{
    GENERATED_BODY()

public:
    FPDAuthLoginRequestData() { }
    FPDAuthLoginRequestData(FString InPlayerId) { PlayerId = InPlayerId; }

    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
