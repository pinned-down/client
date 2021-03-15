#pragma once

#include "CoreMinimal.h"

#include "PDCollectionGetResponseDataItem.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDCollectionGetResponseDataItem
{
    GENERATED_BODY()

public:
    FPDCollectionGetResponseDataItem()
    {
    }

    FPDCollectionGetResponseDataItem(FName InId, int32 InCount)
    {
        Id = InId;
        Count = InCount;
    }

    UPROPERTY(BlueprintReadWrite)
    FName Id;

    UPROPERTY(BlueprintReadWrite)
    int32 Count;
};
