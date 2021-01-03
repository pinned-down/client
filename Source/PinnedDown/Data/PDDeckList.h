#pragma once

#include "CoreMinimal.h"

#include "PDDeckList.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDDeckList
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int64 Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Affiliation;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FName, int32> Cards;
};
