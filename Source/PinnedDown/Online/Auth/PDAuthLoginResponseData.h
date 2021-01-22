#pragma once

#include "CoreMinimal.h"

#include "PDAuthLoginResponseData.generated.h"

USTRUCT()
struct PINNEDDOWN_API FPDAuthLoginResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FString Token;

    UPROPERTY()
    FString Provider;

    UPROPERTY()
    FString ProviderUserId;
};
