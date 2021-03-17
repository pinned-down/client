#pragma once

#include "CoreMinimal.h"

#include "PDDeckListItem.h"

#include "PDDeckList.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckList
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int64 Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FPDDeckListItem> Items;
};
