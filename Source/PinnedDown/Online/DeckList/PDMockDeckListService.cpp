#include "PDMockDeckListService.h"

void UPDMockDeckListService::Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDDeckListGetResponseData Response;

    FPDDeckList BlueWingDeck;
    BlueWingDeck.Id = 1;
    BlueWingDeck.Name = TEXT("Blue Wing");
    BlueWingDeck.Affiliation = TEXT("BlueWing");
    Response.DeckLists.Add(BlueWingDeck);

    FPDDeckList GreenWingDeck;
    GreenWingDeck.Id = 2;
    GreenWingDeck.Name = TEXT("Green Wing");
    GreenWingDeck.Affiliation = TEXT("GreenWing");
    Response.DeckLists.Add(GreenWingDeck);

    FPDDeckList PurpleWingDeck;
    PurpleWingDeck.Id = 3;
    PurpleWingDeck.Name = TEXT("Purple Wing");
    PurpleWingDeck.Affiliation = TEXT("PurpleWing");
    Response.DeckLists.Add(PurpleWingDeck);

    OnSuccess.ExecuteIfBound(Response);
}
