#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDTotalDistanceChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDTotalDistanceChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int32 TotalDistance;
};
