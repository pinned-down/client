#pragma once

#include "CoreMinimal.h"

#include "UI/PDUIMode.h"

#include "PDUIModeMainPhase.generated.h"

class APDCardActor;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIModeMainPhase : public UPDUIMode
{
    GENERATED_BODY()

public:
    virtual void Init(APDPlayerController* InPlayerController, UPDGameplayTagsManager* InGameplayTagsManager) override;

protected:
    void HandleStarshipClicked(APDCardActor* ClickedActor) override;
};
