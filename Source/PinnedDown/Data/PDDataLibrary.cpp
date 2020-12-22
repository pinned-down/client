#include "PDDataLibrary.h"

EPDCardAffiliation UPDDataLibrary::GetDeckAffiliation(const FPDDeckList& DeckList)
{
    if (DeckList.Affiliation == TEXT("BlueWing"))
    {
        return EPDCardAffiliation::AFFILIATION_BlueWing;
    }
    else if (DeckList.Affiliation == TEXT("GreenWing"))
    {
        return EPDCardAffiliation::AFFILIATION_GreenWing;
    }
    else if (DeckList.Affiliation == TEXT("PurpleWing"))
    {
        return EPDCardAffiliation::AFFILIATION_PurpleWing;
    }

    return EPDCardAffiliation::AFFILIATION_Invalid;
}
