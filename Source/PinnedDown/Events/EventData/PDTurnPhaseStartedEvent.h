#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Data/PDTurnPhase.h"

#include "PDTurnPhaseStartedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDTurnPhaseStartedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString TurnPhase;

    UFUNCTION(BlueprintPure)
    EPDTurnPhase GetTurnPhase() const;
};
