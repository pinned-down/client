#include "PDUIModeFightPhase.h"

#include "Core/PDCardActor.h"
#include "Core/PDLog.h"
#include "Core/PDPlayerController.h"
#include "Data/PDAbility.h"
#include "Data/PDAbilityTargetType.h"
#include "Data/Components/PDAbilitiesComponent.h"
#include "Data/Components/PDAssignmentComponent.h"
#include "Data/Components/PDGameplayTagsComponent.h"
#include "Data/Components/PDOwnerComponent.h"

void UPDUIModeFightPhase::HandleCardClicked(APDCardActor* ClickedActor)
{
    Super::HandleCardClicked(ClickedActor);

    // Check clicked card type.
    UPDGameplayTagsComponent* GameplayTagsComponent = ClickedActor->FindComponentByClass<UPDGameplayTagsComponent>();

    if (!IsValid(GameplayTagsComponent))
    {
        return;
    }

    switch (GameplayTagsComponent->GetCardType())
    {
    case EPDCardType::CARDTYPE_Starship:
        HandleStarshipClicked(ClickedActor);
        break;

    case EPDCardType::CARDTYPE_Effect:
        HandleEffectClicked(ClickedActor);
        break;
    }
}

void UPDUIModeFightPhase::HandleStarshipClicked(APDCardActor* ClickedActor)
{
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
    UPDAbilitiesComponent* AbilitiesComponent = ClickedActor->FindComponentByClass<UPDAbilitiesComponent>();

    if (!IsValid(AbilitiesComponent))
    {
        return;
    }

    bool bHasAbilityForFightPhase = false;
    EPDAbilityTargetType AbilityTargetType = EPDAbilityTargetType::TARGETTYPE_Passive;

    for (const FPDAbility& Ability : AbilitiesComponent->GetAbilities())
    {
        if (Ability.GetTurnPhase() == EPDTurnPhase::TURNPHASE_Fight)
        {
            bHasAbilityForFightPhase = true;
            AbilityTargetType = Ability.GetTargetType();
        }
    }

    if (!bHasAbilityForFightPhase)
    {
        return;
    }

    if (AbilityTargetType == EPDAbilityTargetType::TARGETTYPE_Starship)
    {
        EffectToPickTargetFor = ClickedActor;
    }
}
