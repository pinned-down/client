#pragma once

#include "CoreMinimal.h"

#include "PDCollectionOpenCardPackResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDCollectionOpenCardPackResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TMap<FName, int32> AddedItems;
};
