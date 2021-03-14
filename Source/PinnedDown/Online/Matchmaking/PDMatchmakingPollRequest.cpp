#include "PDMatchmakingPollRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDMatchmakingPollRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/open-game-backend-matchmaking/client/pollMatchmaking"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDMatchmakingPollRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDMatchmakingPollRequest::ToString()
{
    return TEXT("FPDMatchmakingPollRequest");
}

void FPDMatchmakingPollRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDMatchmakingPollResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Matchmaking polled - Status: %s, ServerId: %s, IpV4Address: %s, Port: %i"),
        *ResponseData.Status, *ResponseData.ServerId, *ResponseData.IpV4Address, ResponseData.Port);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
