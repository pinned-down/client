#include "PDDataLibrary.h"

EPDCardAffiliation UPDDataLibrary::GetDeckAffiliation(const FPDDeckList& DeckList)
{
    if (DeckList.Type == TEXT("BlueWing"))
    {
        return EPDCardAffiliation::AFFILIATION_BlueWing;
    }
    else if (DeckList.Type == TEXT("GreenWing"))
    {
        return EPDCardAffiliation::AFFILIATION_GreenWing;
    }
    else if (DeckList.Type == TEXT("PurpleWing"))
    {
        return EPDCardAffiliation::AFFILIATION_PurpleWing;
    }

    return EPDCardAffiliation::AFFILIATION_Invalid;
}

int32 UPDDataLibrary::GetCardCount(const FPDDeckList& DeckList, const FName& CardId)
{
    for (const FPDDeckListItem& Item : DeckList.Items)
    {
        if (Item.Id == CardId)
        {
            return Item.Count;
        }
    }

    return 0;
}

void UPDDataLibrary::SetCardCount(FPDDeckList& DeckList, const FName& CardId, int32 NewCount)
{
    for (int32 Index = 0; Index < DeckList.Items.Num(); ++Index)
    {
        FPDDeckListItem& Item = DeckList.Items[Index];

        if (Item.Id == CardId)
        {
            if (NewCount > 0)
            {
                Item.Count = NewCount;
                return;
            }
            else
            {
                DeckList.Items.RemoveAt(Index);
                return;
            }
        }
    }

    if (NewCount <= 0)
    {
        return;
    }

    DeckList.Items.Add(FPDDeckListItem(CardId, NewCount));
}
