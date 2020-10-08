#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Data/PDThreatChangeReason.h"

#include "PDThreatChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDThreatChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int32 OldThreat;

    UPROPERTY(BlueprintReadWrite)
    int32 NewThreat;

    UPROPERTY(BlueprintReadWrite)
    FString Reason;

    UPROPERTY(BlueprintReadWrite)
    FString ReasonEntityBlueprintId;

    UFUNCTION(BlueprintPure)
    int32 GetThreatChange() const;

    UFUNCTION(BlueprintPure)
    EPDThreatChangeReason GetThreatChangeReason() const;

    UFUNCTION(BlueprintPure)
    FName GetThreatChangeReasonCardId() const;
};
