#pragma once

#include "CoreMinimal.h"

#include "Data/PDDeckList.h"

#include "PDDeckListGetResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckListGetResponseData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<FPDDeckList> DeckLists;
};
