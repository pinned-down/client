#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDEndAssignmentPhaseAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDEndAssignmentPhaseAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDEndAssignmentPhaseAction()
    {
        Endpoint = TEXT("/endAssignmentPhase");
    }
};
