#include "PDMockDeckListService.h"

void UPDMockDeckListService::Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDDeckListGetResponseData Response;

    if (DeckLists.Num() == 0)
    {
        FPDDeckList BlueWingDeck;
        BlueWingDeck.Id = 1;
        BlueWingDeck.Type = TEXT("BlueWingDeck");
        BlueWingDeck.Items.Add(FPDDeckListItem(TEXT("Defiance"), 4));
        BlueWingDeck.Items.Add(FPDDeckListItem(TEXT("TRBArdor"), 1));
        DeckLists.Add(BlueWingDeck);

        FPDDeckList GreenWingDeck;
        GreenWingDeck.Id = 2;
        GreenWingDeck.Type = TEXT("GreenWingDeck");
        DeckLists.Add(GreenWingDeck);

        FPDDeckList PurpleWingDeck;
        PurpleWingDeck.Id = 3;
        PurpleWingDeck.Type = TEXT("PurpleWingDeck");
        DeckLists.Add(PurpleWingDeck);
    }
    
    Response.Loadouts = DeckLists;
    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockDeckListService::Put(int64 LoadoutId, const FPDDeckListPutRequestData& RequestData, const FPDDeckListPutSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    for (FPDDeckList& DeckList : DeckLists)
    {
        if (DeckList.Id != LoadoutId)
        {
            continue;
        }

        DeckList.Type = RequestData.Type;
        DeckList.Items = RequestData.Items;
    }

    OnSuccess.ExecuteIfBound();
}
