#include "PDUIMode.h"

#include "Core/PDCardActor.h"
#include "Data/PDCardType.h"
#include "Data/Components/PDGameplayTagsComponent.h"

void UPDUIMode::Init(APDPlayerController* InPlayerController, UPDGameplayTagsManager* InGameplayTagsManager)
{
    PlayerController = InPlayerController;
    GameplayTagsManager = InGameplayTagsManager;
}

void UPDUIMode::HandleCardClicked(APDCardActor* ClickedActor)
{
    // Check clicked card type.
    UPDGameplayTagsComponent* GameplayTagsComponent = ClickedActor->FindComponentByClass<UPDGameplayTagsComponent>();

    if (!IsValid(GameplayTagsComponent))
    {
        return;
    }

    switch (GameplayTagsComponent->GetCardType())
    {
    case EPDCardType::CARDTYPE_Effect:
        HandleEffectClicked(ClickedActor);
        break;

    case EPDCardType::CARDTYPE_Starship:
        HandleStarshipClicked(ClickedActor);
        break;
    }
}

UPDGameplayTagsManager* UPDUIMode::GetGameplayTagsManager() const
{
    return GameplayTagsManager;
}

APDPlayerController* UPDUIMode::GetPlayerController() const
{
    return PlayerController;
}

void UPDUIMode::HandleEffectClicked(APDCardActor* ClickedActor)
{
}

void UPDUIMode::HandleStarshipClicked(APDCardActor* ClickedActor)
{
}

void UPDUIMode::NotifyOnHintChanged(const FText& Hint)
{
    OnHintChanged.Broadcast(Hint);
}
