#pragma once

#include "CoreMinimal.h"

#include "PDCollectionGetResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDCollectionGetResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TMap<FName, int32> Collection;
};
