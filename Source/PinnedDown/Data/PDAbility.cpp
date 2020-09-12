#include "PDAbility.h"

#include "Core/PDCardActor.h"
#include "Core/PDLog.h"
#include "Data/Components/PDGameplayTagsComponent.h"

EPDAbilityTargetType FPDAbility::GetTargetType() const
{
    if (TargetType == TEXT("Starship"))
    {
        return EPDAbilityTargetType::TARGETTYPE_Starship;
    }

    return EPDAbilityTargetType::TARGETTYPE_Passive;
}

EPDTurnPhase FPDAbility::GetTurnPhase() const
{
    for (const FString& Tag : RequiredTags)
    {
        if (Tag == TEXT("TurnPhase.Main"))
        {
            return EPDTurnPhase::TURNPHASE_Main;
        }

        if (Tag == TEXT("TurnPhase.Attack"))
        {
            return EPDTurnPhase::TURNPHASE_Assignment;
        }

        if (Tag == TEXT("TurnPhase.Assignment"))
        {
            return EPDTurnPhase::TURNPHASE_Assignment;
        }

        if (Tag == TEXT("TurnPhase.Fight"))
        {
            return EPDTurnPhase::TURNPHASE_Fight;
        }

        if (Tag == TEXT("TurnPhase.Jump"))
        {
            return EPDTurnPhase::TURNPHASE_Jump;
        }
    }

    return EPDTurnPhase::TURNPHASE_Invalid;
}

bool FPDAbility::IsValidTarget(const APDCardActor* Target) const
{
    if (!IsValid(Target))
    {
        return false;
    }

    const UPDGameplayTagsComponent* GameplayTagsComponent = Target->FindComponentByClass<UPDGameplayTagsComponent>();

    if (!IsValid(GameplayTagsComponent))
    {
        return false;
    }

    for (const FString& RequiredTag : TargetRequiredTags)
    {
        if (!GameplayTagsComponent->GetInitialGameplayTags().Contains(RequiredTag))
        {
            return false;
        }
    }

    for (const FString& BlockedTag : TargetBlockedTags)
    {
        if (GameplayTagsComponent->GetInitialGameplayTags().Contains(BlockedTag))
        {
            return false;
        }
    }

    return true;
}
