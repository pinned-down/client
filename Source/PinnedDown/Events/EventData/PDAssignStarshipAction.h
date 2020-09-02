#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDAssignStarshipAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAssignStarshipAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDAssignStarshipAction()
    {
        Endpoint = TEXT("/assignStarship");
    }

    UPROPERTY(BlueprintReadWrite)
    int64 AssignedStarship;

    UPROPERTY(BlueprintReadWrite)
    int64 AssignedTo;
};
