#include "PDMatchmakingEnqueueRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDMatchmakingEnqueueRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/open-game-backend-matchmaking/client/enqueue"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDMatchmakingEnqueueRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDMatchmakingEnqueueRequest::ToString()
{
    return FString::Printf(TEXT("FPDMatchmakingEnqueueRequest - Player Id: %s, Version: %s, Game Mode: %s, Region: %s"),
        *RequestData.PlayerId, *RequestData.Version, *RequestData.GameMode, *RequestData.Region);
}

void FPDMatchmakingEnqueueRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDMatchmakingEnqueueResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Enqueued - Matchmaking status: %s"), *ResponseData.Status);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
