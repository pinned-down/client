#include "PDOwnerComponent.h"

int64 UPDOwnerComponent::GetOwnerEntityId() const
{
    return OwnerEntityId;
}

void UPDOwnerComponent::SetOwnerEntityId(int64 InOwnerEntityId)
{
    OwnerEntityId = InOwnerEntityId;
}
