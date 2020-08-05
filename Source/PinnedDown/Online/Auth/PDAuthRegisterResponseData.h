#pragma once

#include "CoreMinimal.h"

#include "PDAuthRegisterResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAuthRegisterResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FString PlayerId;
};
