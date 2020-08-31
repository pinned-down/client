#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDCurrentLocationChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDCurrentLocationChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;

    UPROPERTY(BlueprintReadWrite)
    FString BlueprintId;
};
