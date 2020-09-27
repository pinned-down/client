#pragma once

#include "CoreMinimal.h"

#include "UI/PDUIMode.h"

#include "PDUIModeFightPhase.generated.h"

class APDCardActor;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIModeFightPhase : public UPDUIMode
{
    GENERATED_BODY()

protected:
    void HandleStarshipClicked(APDCardActor* ClickedActor) override;
    void HandleEffectClicked(APDCardActor* ClickedActor) override;

private:
    UPROPERTY()
    APDCardActor* EffectToPickTargetFor;
};
