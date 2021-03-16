#pragma once

#include "CoreMinimal.h"

#include "PDCollectionClaimResponseDataItem.h"

#include "PDCollectionClaimResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDCollectionClaimResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString ItemSetId;

    UPROPERTY(BlueprintReadWrite)
    TArray<FPDCollectionClaimResponseDataItem> Items;
};
