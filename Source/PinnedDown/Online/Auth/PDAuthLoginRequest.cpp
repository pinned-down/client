#include "PDAuthLoginRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDAuthLoginRequest::Execute()
{
    TSharedRef<IHttpRequest> Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/open-game-backend-auth/login"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDAuthLoginRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDAuthLoginRequest::ToString()
{
    return TEXT("FPDAuthLoginRequest");
}

void FPDAuthLoginRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDAuthLoginResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Login successful - Token: %s"), *ResponseData.Token);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
