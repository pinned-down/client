#pragma once

#include "CoreMinimal.h"

#include "PDDeckListPutRequestData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckListPutRequestData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 Id;

    UPROPERTY(BlueprintReadWrite)
    FString Name;

    UPROPERTY(BlueprintReadWrite)
    FString Affiliation;

    UPROPERTY(BlueprintReadWrite)
    TMap<FName, int32> Cards;
};
