#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDUIMode.generated.h"

class APDCardActor;
class UPDGameplayTagsManager;
class APDPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDUIModeHintChangedSignature, const FText&, Hint);

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDUIMode : public UObject
{
    GENERATED_BODY()

public:
    virtual void Init(APDPlayerController* InPlayerController, UPDGameplayTagsManager* InGameplayTagsManager);
    virtual void HandleCardClicked(APDCardActor* ClickedActor);

    UPDGameplayTagsManager* GetGameplayTagsManager() const;
    APDPlayerController* GetPlayerController() const;

    UPROPERTY(BlueprintAssignable)
    FPDUIModeHintChangedSignature OnHintChanged;

protected:
    virtual void HandleEffectClicked(APDCardActor* ClickedActor);
    virtual void HandleStarshipClicked(APDCardActor* ClickedActor);

    virtual void NotifyOnHintChanged(const FText& Hint);

private:
    UPROPERTY()
    UPDGameplayTagsManager* GameplayTagsManager;

    UPROPERTY()
    APDPlayerController* PlayerController;
};
