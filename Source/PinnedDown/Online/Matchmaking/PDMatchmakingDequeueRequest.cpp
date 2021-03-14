#include "PDMatchmakingDequeueRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDMatchmakingDequeueRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/open-game-backend-matchmaking/client/dequeue"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDMatchmakingDequeueRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDMatchmakingDequeueRequest::ToString()
{
    return TEXT("FPDMatchmakingDequeueRequest");
}

void FPDMatchmakingDequeueRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDMatchmakingDequeueResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
