#include "PDGameplayTagsComponent.h"

EPDCardType UPDGameplayTagsComponent::GetCardType() const
{
    for (const FString& TagName : InitialGameplayTags)
    {
        if (TagName == TEXT("CardType.Damage"))
        {
            return EPDCardType::CARDTYPE_Damage;
        }
        else if (TagName == TEXT("CardType.Effect"))
        {
            return EPDCardType::CARDTYPE_Effect;
        }
        else if (TagName == TEXT("CardType.Location"))
        {
            return EPDCardType::CARDTYPE_Location;
        }
        else if (TagName == TEXT("CardType.Starship"))
        {
            return EPDCardType::CARDTYPE_Starship;
        }
    }

    return EPDCardType::CARDTYPE_Invalid;
}

EPDCardAffiliation UPDGameplayTagsComponent::GetCardAffiliation() const
{
    for (const FString& TagName : InitialGameplayTags)
    {
        if (TagName == TEXT("Affiliation.BlueWing"))
        {
            return EPDCardAffiliation::AFFILIATION_BlueWing;
        }
        else if (TagName == TEXT("Affiliation.GreenWing"))
        {
            return EPDCardAffiliation::AFFILIATION_GreenWing;
        }
        else if (TagName == TEXT("Affiliation.PurpleWing"))
        {
            return EPDCardAffiliation::AFFILIATION_PurpleWing;
        }
        else if (TagName == TEXT("Affiliation.DraTar"))
        {
            return EPDCardAffiliation::AFFILIATION_DraTar;
        }
    }

    return EPDCardAffiliation::AFFILIATION_Invalid;
}
