#include "PDCheatManager.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDGameMode.h"
#include "Events/EventData/PDGodCheatAction.h"

void UPDCheatManager::God()
{
    Super::God();

    UPDGodCheatAction* Action = NewObject<UPDGodCheatAction>(this);

    APDGameMode* GameMode = Cast<APDGameMode>(UGameplayStatics::GetGameMode(this));

    if (!IsValid(GameMode))
    {
        return;
    }

    GameMode->SendActionToServer(Action);
}
