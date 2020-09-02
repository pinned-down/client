#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDEndMainPhaseAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDEndMainPhaseAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDEndMainPhaseAction()
    {
        Endpoint = TEXT("/endMainPhase");
    }
};
