#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDStarshipAssignedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDStarshipAssignedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 AssignedStarship;

    UPROPERTY(BlueprintReadWrite)
    int64 AssignedTo;
};
