#pragma once

#include "CoreMinimal.h"

#include "PDAuthRegisterRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAuthRegisterRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString Nickname;
};
