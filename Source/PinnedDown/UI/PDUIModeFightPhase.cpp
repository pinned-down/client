#include "PDUIModeFightPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDPlayerController.h"
#include "Data/Components/PDAssignmentComponent.h"
#include "Data/Components/PDOwnerComponent.h"

void UPDUIModeFightPhase::HandleCardClicked(APDCardActor* ClickedActor)
{
    Super::HandleCardClicked(ClickedActor);

    // Check if clicked player card.
    UPDOwnerComponent* OwnerComponent = ClickedActor->FindComponentByClass<UPDOwnerComponent>();

    if (!IsValid(OwnerComponent) || !GetPlayerController()->IsLocalPlayer(OwnerComponent->GetOwnerEntityId()))
    {
        return;
    }

    // Check if assigned.
    UPDAssignmentComponent* AssignmentComponent = ClickedActor->FindComponentByClass<UPDAssignmentComponent>();

    if (!IsValid(AssignmentComponent) || !IsValid(AssignmentComponent->GetAssignedTo()))
    {
        return;
    }

    // Resolve fight.
    GetPlayerController()->ServerResolveFight(ClickedActor->GetEntityId());
}

