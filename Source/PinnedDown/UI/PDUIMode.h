#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDUIMode.generated.h"

class APDCardActor;
class APDPlayerController;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIMode : public UObject
{
    GENERATED_BODY()

public:
    virtual void Init(APDPlayerController* InPlayerController);
    virtual void HandleCardClicked(APDCardActor* ClickedActor);

    APDPlayerController* GetPlayerController() const;

private:
    UPROPERTY()
    APDPlayerController* PlayerController;
};
