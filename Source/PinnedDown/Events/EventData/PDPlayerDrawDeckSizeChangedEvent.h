#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDPlayerDrawDeckSizeChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPlayerDrawDeckSizeChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 PlayerEntityId;

    UPROPERTY(BlueprintReadWrite)
    int32 DrawDeckSize;
};
