#pragma once

#include "CoreMinimal.h"

#include "Events/PDAction.h"

#include "PDPlayEffectAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPlayEffectAction : public UPDAction
{
    GENERATED_BODY()

public:
    UPDPlayEffectAction()
    {
        Endpoint = TEXT("/playEffect");
    }

    UPROPERTY(BlueprintReadWrite)
    FString BlueprintId;

    UPROPERTY(BlueprintReadWrite)
    int64 TargetEntityId;
};
