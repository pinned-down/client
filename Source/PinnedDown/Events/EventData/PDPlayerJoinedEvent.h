#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDPlayerJoinedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPlayerJoinedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
