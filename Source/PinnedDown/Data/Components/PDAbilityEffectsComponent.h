#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Data/PDActiveAbilityEffect.h"

#include "PDAbilityEffectsComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAbilityEffectsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    TArray<FPDActiveAbilityEffect> GetActiveEffects() const;

    void AddActiveEffect(int64 EntityId, FPDActiveAbilityEffect Effect);
    void RemoveActiveEffect(int64 EntityId);

private:
    UPROPERTY(VisibleAnywhere)
    TMap<int64, FPDActiveAbilityEffect> ActiveEffects;
};
