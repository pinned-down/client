#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDStarshipPowerChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDStarshipPowerChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;

    UPROPERTY(BlueprintReadWrite)
    int32 OldPowerModifier;

    UPROPERTY(BlueprintReadWrite)
    int32 NewPowerModifier;
};
