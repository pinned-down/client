#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDPowerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPDPowerComponentPowerChangedSignature, AActor*, Actor, int32, OldPowerModifier, int32, NewPowerModifier);

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPowerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    int32 GetBasePower() const;

    UFUNCTION(BlueprintPure)
    int32 GetPowerModifier() const;

    void SetPowerModifier(int32 InPowerModifier);

    UPROPERTY(BlueprintAssignable)
    FPDPowerComponentPowerChangedSignature OnPowerChanged;

private:
    UPROPERTY(VisibleAnywhere)
    int32 BasePower;

    UPROPERTY(VisibleAnywhere)
    int32 PowerModifier;
};
