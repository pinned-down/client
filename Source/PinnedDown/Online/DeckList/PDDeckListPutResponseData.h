#pragma once

#include "CoreMinimal.h"

#include "PDDeckListPutResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckListPutResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 Id;
};
