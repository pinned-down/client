#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDPlayStarshipAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPlayStarshipAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDPlayStarshipAction()
    {
        Endpoint = TEXT("/playStarship");
    }

    UPROPERTY(BlueprintReadWrite)
    FString BlueprintId;
};
