#include "PDUIModeFightPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDGameplayTagsManager.h"
#include "Core/PDPlayerController.h"
#include "Data/PDAbility.h"
#include "Data/PDAbilityTargetType.h"
#include "Data/Components/PDAbilitiesComponent.h"
#include "Data/Components/PDAssignmentComponent.h"

#include "Data/Components/PDOwnerComponent.h"

void UPDUIModeFightPhase::Init(APDPlayerController* InPlayerController, UPDGameplayTagsManager* InGameplayTagsManager)
{
    Super::Init(InPlayerController, InGameplayTagsManager);

    OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.FightPhase.ChooseAction", "Click on a starship to resolve its fight, or select an effect from hand to play!"));
}

void UPDUIModeFightPhase::HandleStarshipClicked(APDCardActor* ClickedActor)
{
    Super::HandleStarshipClicked(ClickedActor);

    if (IsValid(EffectToPickTargetFor))
    {
        UPDAbilitiesComponent* AbilitiesComponent = EffectToPickTargetFor->FindComponentByClass<UPDAbilitiesComponent>();

        if (!IsValid(AbilitiesComponent))
        {
            return;
        }

        for (const FPDAbility& Ability : AbilitiesComponent->GetAbilities())
        {
            // Check if any ability has valid target.
            if (Ability.IsValidTarget(ClickedActor))
            {
                GetPlayerController()->ServerPlayEffect(EffectToPickTargetFor->GetCardId().ToString(), ClickedActor->GetEntityId());
                return;
            }
        }

        EffectToPickTargetFor = nullptr;

        OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.FightPhase.ChooseAction", "Click on a starship to resolve its fight, or select an effect from hand to play!"));
        return;
    }

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

void UPDUIModeFightPhase::HandleEffectClicked(APDCardActor* ClickedActor)
{
    Super::HandleEffectClicked(ClickedActor);

    UPDAbilitiesComponent* AbilitiesComponent = ClickedActor->FindComponentByClass<UPDAbilitiesComponent>();

    if (!IsValid(AbilitiesComponent))
    {
        return;
    }

    bool bMeetsRequiredTags = false;
    EPDAbilityTargetType AbilityTargetType = EPDAbilityTargetType::TARGETTYPE_Passive;

    for (const FPDAbility& Ability : AbilitiesComponent->GetAbilities())
    {
        if (GetGameplayTagsManager()->HasAllGlobalTags(Ability.RequiredTags))
        {
            bMeetsRequiredTags = true;
            AbilityTargetType = Ability.GetTargetType();
            break;
        }
    }

    if (!bMeetsRequiredTags)
    {
        return;
    }

    if (AbilityTargetType == EPDAbilityTargetType::TARGETTYPE_Starship)
    {
        EffectToPickTargetFor = ClickedActor;

        OnHintChanged.Broadcast(NSLOCTEXT("PinnedDown", "UIMode.FightPhase.SelectEffectTarget", "Select a target!"));
    }
}
