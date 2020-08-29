#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDPowerComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDPowerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    int32 GetBasePower() const;

    UFUNCTION(BlueprintPure)
    int32 GetPowerModifier() const;

private:
    UPROPERTY(VisibleAnywhere)
    int32 BasePower;

    UPROPERTY(VisibleAnywhere)
    int32 PowerModifier;
};
