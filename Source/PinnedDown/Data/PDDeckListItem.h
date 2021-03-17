#pragma once

#include "CoreMinimal.h"

#include "PDDeckListItem.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckListItem
{
    GENERATED_BODY()

public:
    FPDDeckListItem()
    {
    }

    FPDDeckListItem(FName InId, int32 InCount)
    {
        Id = InId;
        Count = InCount;
    }

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 Count;
};
