#include "PDAuthLoginRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineLibrary.h"
#include "Online/PDOnlineLog.h"

void FPDAuthLoginRequest::Execute()
{
    TSharedRef<IHttpRequest> Request = UPDOnlineLibrary::CreateHttpRequest(TEXT("/open-game-backend-auth/login"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDAuthLoginRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        PDBroadcastDynamicMulticastDelegate(OnError, NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDAuthLoginRequest::ToString()
{
    return TEXT("FPDAuthLoginRequest");
}

void FPDAuthLoginRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    FString ErrorMessage = CheckForErrors(Response, bWasSuccessful);

    if (!ErrorMessage.IsEmpty())
    {
        PDBroadcastDynamicMulticastDelegate(OnError, ErrorMessage);
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDAuthLoginResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Login successful - Token: %s"), *ResponseData.Token);

    PDBroadcastDynamicMulticastDelegate(OnSuccess, ResponseData);
}
