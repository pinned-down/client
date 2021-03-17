#include "PDDeckListPutRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDDeckListPutRequest::Execute()
{
    FHttpRequestRef Request = LoadoutId != 0
        ? HttpRequestBuilder->CreateHttpPutRequest(FString::Printf(TEXT("/open-game-backend-collection/client/loadouts/%ld"), LoadoutId), RequestData)
        : HttpRequestBuilder->CreateHttpRequest(TEXT("/open-game-backend-collection/client/loadouts"), RequestData);

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

    if (LoadoutId != 0)
    {
        UE_LOG(LogPDOnline, Log, TEXT("Deck list updated - Id: %ld"), LoadoutId);
    }
    else
    {
        UE_LOG(LogPDOnline, Log, TEXT("Deck list created - Type: %s"), *RequestData.Type);
    }
    
    OnServiceSuccess.ExecuteIfBound();
}
