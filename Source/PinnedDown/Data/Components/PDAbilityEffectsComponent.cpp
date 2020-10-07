#include "PDAbilityEffectsComponent.h"

TArray<FPDActiveAbilityEffect> UPDAbilityEffectsComponent::GetActiveEffects() const
{
    TArray<FPDActiveAbilityEffect> OutActiveEffects;
    ActiveEffects.GenerateValueArray(OutActiveEffects);
    return OutActiveEffects;
}

void UPDAbilityEffectsComponent::AddActiveEffect(int64 EntityId, FPDActiveAbilityEffect Effect)
{
    ActiveEffects.Add(EntityId, Effect);
}

void UPDAbilityEffectsComponent::RemoveActiveEffect(int64 EntityId)
{
    ActiveEffects.Remove(EntityId);
}
