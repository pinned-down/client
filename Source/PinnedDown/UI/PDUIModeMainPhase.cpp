#include "PDUIModeMainPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDPlayerController.h"

void UPDUIModeMainPhase::Init(APDPlayerController* InPlayerController, UPDGameplayTagsManager* InGameplayTagsManager)
{
    Super::Init(InPlayerController, InGameplayTagsManager);

    OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.MainPhase.PlayStarship", "Click on a starship card in your hand to deploy that starship!"));
}

void UPDUIModeMainPhase::HandleStarshipClicked(APDCardActor* ClickedActor)
{
    Super::HandleStarshipClicked(ClickedActor);

    GetPlayerController()->ServerPlayStarship(ClickedActor->GetCardId().ToString());
}
