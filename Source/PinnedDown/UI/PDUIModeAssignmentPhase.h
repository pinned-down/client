#pragma once

#include "CoreMinimal.h"

#include "UI/PDUIMode.h"

#include "PDUIModeAssignmentPhase.generated.h"

class APDCardActor;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIModeAssignmentPhase : public UPDUIMode
{
    GENERATED_BODY()

public:
    virtual void HandleCardClicked(APDCardActor* ClickedActor);

private:
    UPROPERTY()
    APDCardActor* SelectedPlayerCard;
};
