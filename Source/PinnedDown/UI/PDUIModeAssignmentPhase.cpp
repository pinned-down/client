#include "PDUIModeAssignmentPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDPlayerController.h"
#include "Data/Components/PDOwnerComponent.h"

void UPDUIModeAssignmentPhase::Init(APDPlayerController* InPlayerController, UPDGameplayTagsManager* InGameplayTagsManager)
{
    Super::Init(InPlayerController, InGameplayTagsManager);

    OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.AssignmentPhase.Assign", "Select a starship to assign to an enemy!"));
}

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

            OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.AssignmentPhase.AssignTo", "Select an enemy starship to assign your starship to!"));
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

            OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.AssignmentPhase.Assign", "Select a starship to assign to an enemy!"));
        }
    }
}

