#pragma once

#include "CoreMinimal.h"

#include "UI/PDUIMode.h"

#include "PDUIModeFightPhase.generated.h"

class APDCardActor;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIModeFightPhase : public UPDUIMode
{
    GENERATED_BODY()

public:
    virtual void HandleCardClicked(APDCardActor* ClickedActor);

private:
    UPROPERTY()
    APDCardActor* EffectToPickTargetFor;

    void HandleStarshipClicked(APDCardActor* ClickedActor);
    void HandleEffectClicked(APDCardActor* ClickedActor);
};
