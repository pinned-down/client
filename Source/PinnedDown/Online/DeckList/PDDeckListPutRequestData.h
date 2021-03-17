#pragma once

#include "CoreMinimal.h"

#include "Data/PDDeckListItem.h"

#include "PDDeckListPutRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckListPutRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString Type;

    UPROPERTY(BlueprintReadWrite)
    TArray<FPDDeckListItem> Items;
};
