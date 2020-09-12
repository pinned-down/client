#include "PDPowerComponent.h"

int32 UPDPowerComponent::GetBasePower() const
{
    return BasePower;
}

int32 UPDPowerComponent::GetPowerModifier() const
{
    return PowerModifier;
}

void UPDPowerComponent::SetPowerModifier(int32 InPowerModifier)
{
    if (PowerModifier == InPowerModifier)
    {
        return;
    }

    int32 OldPowerModifier = PowerModifier;
    PowerModifier = InPowerModifier;

    // Notify listeners.
    OnPowerChanged.Broadcast(GetOwner(), OldPowerModifier, PowerModifier);
}
