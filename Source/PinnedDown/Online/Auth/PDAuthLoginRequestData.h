#pragma once

#include "CoreMinimal.h"

#include "PDAuthLoginRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAuthLoginRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString Provider;

    UPROPERTY(BlueprintReadWrite)
    FString Key;

    UPROPERTY(BlueprintReadWrite)
    FString Context;

    UPROPERTY(BlueprintReadWrite)
    FString Role;
};
