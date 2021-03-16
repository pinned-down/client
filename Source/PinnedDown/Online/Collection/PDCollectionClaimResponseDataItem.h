#pragma once

#include "CoreMinimal.h"

#include "PDCollectionClaimResponseDataItem.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDCollectionClaimResponseDataItem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FName Id;

    UPROPERTY(BlueprintReadWrite)
    int32 Count;
};
