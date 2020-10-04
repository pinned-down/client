#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDErrorEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDErrorEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString ActionId;

    UPROPERTY(BlueprintReadWrite)
    FString ErrorCode;
};
