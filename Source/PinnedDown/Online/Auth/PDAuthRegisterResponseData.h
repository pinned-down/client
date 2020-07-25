#pragma once

#include "CoreMinimal.h"

#include "PDAuthRegisterResponseData.generated.h"

USTRUCT()
struct PINNEDDOWN_API FPDAuthRegisterResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FString PlayerId;
};
