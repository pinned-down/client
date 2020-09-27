#include "PDUIModeMainPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDPlayerController.h"

void UPDUIModeMainPhase::HandleStarshipClicked(APDCardActor* ClickedActor)
{
    Super::HandleStarshipClicked(ClickedActor);

    GetPlayerController()->ServerPlayStarship(ClickedActor->GetCardId().ToString());
}
