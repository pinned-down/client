#include "PDUIMode.h"

void UPDUIMode::Init(APDPlayerController* InPlayerController)
{
    PlayerController = InPlayerController;
}

void UPDUIMode::HandleCardClicked(APDCardActor* ClickedActor)
{
}

APDPlayerController* UPDUIMode::GetPlayerController() const
{
    return PlayerController;
}
