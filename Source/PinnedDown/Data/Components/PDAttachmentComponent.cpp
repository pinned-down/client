#include "PDAttachmentComponent.h"

APDCardActor* UPDAttachmentComponent::GetAttachedTo() const
{
    return AttachedTo;
}

void UPDAttachmentComponent::SetAttachedTo(APDCardActor* InAttachedTo)
{
    AttachedTo = InAttachedTo;
}
