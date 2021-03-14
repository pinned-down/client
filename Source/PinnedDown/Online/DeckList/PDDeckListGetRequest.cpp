#include "PDDeckListGetRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDDeckListGetRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/pinneddown-decklist/get"));

    Request->OnProcessRequestComplete().BindRaw(this, &FPDDeckListGetRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDDeckListGetRequest::ToString()
{
    return TEXT("FPDDeckListGetRequest");
}

void FPDDeckListGetRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDDeckListGetResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Deck Lists Fetched - Num: %i"), ResponseData.DeckLists.Num());

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
