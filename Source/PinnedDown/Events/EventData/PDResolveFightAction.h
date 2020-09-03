#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDResolveFightAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDResolveFightAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDResolveFightAction()
    {
        Endpoint = TEXT("/resolveFight");
    }

    UPROPERTY(BlueprintReadWrite)
    int64 EntityId;
};
