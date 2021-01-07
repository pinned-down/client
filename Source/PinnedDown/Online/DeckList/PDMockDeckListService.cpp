#include "PDMockDeckListService.h"

void UPDMockDeckListService::Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDDeckListGetResponseData Response;

    if (DeckLists.Num() == 0)
    {
        FPDDeckList BlueWingDeck;
        BlueWingDeck.Id = 1;
        BlueWingDeck.Name = TEXT("Blue Wing");
        BlueWingDeck.Affiliation = TEXT("BlueWing");
        BlueWingDeck.Cards.Add(TEXT("Defiance"), 4);
        BlueWingDeck.Cards.Add(TEXT("TRBArdor"), 1);
        DeckLists.Add(BlueWingDeck);

        FPDDeckList GreenWingDeck;
        GreenWingDeck.Id = 2;
        GreenWingDeck.Name = TEXT("Green Wing");
        GreenWingDeck.Affiliation = TEXT("GreenWing");
        DeckLists.Add(GreenWingDeck);

        FPDDeckList PurpleWingDeck;
        PurpleWingDeck.Id = 3;
        PurpleWingDeck.Name = TEXT("Purple Wing");
        PurpleWingDeck.Affiliation = TEXT("PurpleWing");
        DeckLists.Add(PurpleWingDeck);
    }
    
    Response.DeckLists = DeckLists;
    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockDeckListService::Put(const FPDDeckListPutRequestData& RequestData, const FPDDeckListPutSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    for (FPDDeckList& DeckList : DeckLists)
    {
        if (DeckList.Id != RequestData.Id)
        {
            continue;
        }

        DeckList.Name = RequestData.Name;
        DeckList.Affiliation = RequestData.Affiliation;
        DeckList.Cards = RequestData.Cards;
    }

    FPDDeckListPutResponseData Response;
    Response.Id = RequestData.Id;
    OnSuccess.ExecuteIfBound(Response);
}
