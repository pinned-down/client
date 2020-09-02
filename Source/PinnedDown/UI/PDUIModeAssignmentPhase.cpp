#include "PDUIModeAssignmentPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDPlayerController.h"
#include "Data/Components/PDOwnerComponent.h"

void UPDUIModeAssignmentPhase::HandleCardClicked(APDCardActor* ClickedActor)
{
    Super::HandleCardClicked(ClickedActor);

    if (!IsValid(SelectedPlayerCard))
    {
        // Try to select player card to assign.
        UPDOwnerComponent* OwnerComponent = ClickedActor->FindComponentByClass<UPDOwnerComponent>();
        
        if (GetPlayerController()->IsLocalPlayer(OwnerComponent->GetOwnerEntityId()))
        {
            SelectedPlayerCard = ClickedActor;
        }
    }
    else
    {
        // Try to assign to enemy card.
        UPDOwnerComponent* OwnerComponent = ClickedActor->FindComponentByClass<UPDOwnerComponent>();

        if (!GetPlayerController()->IsLocalPlayer(OwnerComponent->GetOwnerEntityId()))
        {
            // Assign card.
            GetPlayerController()->ServerAssignStarship(SelectedPlayerCard->GetEntityId(), ClickedActor->GetEntityId());

            SelectedPlayerCard = nullptr;
        }
    }
}

