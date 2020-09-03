#include "PDAssignmentComponent.h"

APDCardActor* UPDAssignmentComponent::GetAssignedTo() const
{
    return AssignedTo;
}

void UPDAssignmentComponent::SetAssignedTo(APDCardActor* InAssignedTo)
{
    AssignedTo = InAssignedTo;
}
