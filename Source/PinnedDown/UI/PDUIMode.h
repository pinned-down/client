#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDUIMode.generated.h"

class APDCardActor;
class UPDGameplayTagsManager;
class APDPlayerController;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIMode : public UObject
{
    GENERATED_BODY()

public:
    virtual void Init(APDPlayerController* InPlayerController);
    virtual void HandleCardClicked(APDCardActor* ClickedActor);

    UPDGameplayTagsManager* GetGameplayTagsManager() const;
    APDPlayerController* GetPlayerController() const;

protected:
    virtual void HandleEffectClicked(APDCardActor* ClickedActor);
    virtual void HandleStarshipClicked(APDCardActor* ClickedActor);

private:
    UPROPERTY(meta = (Inject))
    UPDGameplayTagsManager* GameplayTagsManager;

    UPROPERTY()
    APDPlayerController* PlayerController;
};
