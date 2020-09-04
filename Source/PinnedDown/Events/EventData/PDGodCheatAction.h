#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDGodCheatAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDGodCheatAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDGodCheatAction()
    {
        Endpoint = TEXT("/godCheat");
    }
};
