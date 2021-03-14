#include "PDDeckListPutRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDDeckListPutRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/pinneddown-decklist/put"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDDeckListPutRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDDeckListPutRequest::ToString()
{
    return TEXT("FPDDeckListPutRequest");
}

void FPDDeckListPutRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDDeckListPutResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Deck list updated - Id: %d"), ResponseData.Id);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
