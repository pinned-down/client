#pragma once

#include "CoreMinimal.h"

#include "PDCollectionGetResponseDataItem.h"

#include "PDCollectionGetResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDCollectionGetResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<FPDCollectionGetResponseDataItem> Collection;
};
