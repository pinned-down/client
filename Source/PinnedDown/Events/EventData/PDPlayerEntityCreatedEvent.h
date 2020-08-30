#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDPlayerEntityCreatedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPlayerEntityCreatedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;

    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;
};
