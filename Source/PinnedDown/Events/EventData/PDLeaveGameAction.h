#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDLeaveGameAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDLeaveGameAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDLeaveGameAction()
    {
        Endpoint = TEXT("/leave");
    }

    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
