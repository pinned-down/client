#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDPlayerHandChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPlayerHandChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 PlayerEntityId;

    UPROPERTY(BlueprintReadWrite)
    TArray<FString> Cards;
};
