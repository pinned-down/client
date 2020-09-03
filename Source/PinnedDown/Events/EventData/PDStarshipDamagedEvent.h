#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDStarshipDamagedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDStarshipDamagedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 StarshipEntityId;

    UPROPERTY(BlueprintReadWrite)
    int64 DamageEntityId;

    UPROPERTY(BlueprintReadWrite)
    FString DamageBlueprintId;
};
