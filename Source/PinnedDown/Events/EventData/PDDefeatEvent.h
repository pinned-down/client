#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Data/PDDefeatReason.h"

#include "PDDefeatEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDDefeatEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString Reason;

    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;
    
    UFUNCTION(BlueprintPure)
    EPDDefeatReason GetDefeatReason() const;
};
