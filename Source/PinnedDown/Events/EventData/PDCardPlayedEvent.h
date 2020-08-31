#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDCardPlayedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDCardPlayedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;

    UPROPERTY(BlueprintReadWrite)
    FString BlueprintId;

    UPROPERTY(BlueprintReadWrite)
    int64 OwnerEntityId;
};
