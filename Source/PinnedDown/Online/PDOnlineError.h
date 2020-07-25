#pragma once

#include "CoreMinimal.h"

#include "PDOnlineError.generated.h"

USTRUCT()
struct PINNEDDOWN_API FPDOnlineError
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 ErrorCode;

    UPROPERTY()
    FString ErrorMessage;
};
