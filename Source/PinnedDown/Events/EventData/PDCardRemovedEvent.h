#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDCardRemovedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDCardRemovedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;
};
