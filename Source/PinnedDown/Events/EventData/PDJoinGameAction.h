#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDJoinGameAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDJoinGameAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDJoinGameAction()
    {
        Endpoint = TEXT("/join");
    }

    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
