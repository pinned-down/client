#include "PDAuthRegisterRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineLibrary.h"
#include "Online/PDOnlineLog.h"

void FPDAuthRegisterRequest::Execute()
{
    TSharedRef<IHttpRequest> Request = UPDOnlineLibrary::CreateHttpRequest(TEXT("/open-game-backend-auth/register"), RequestData);

    Request->OnProcessRequestComplete().BindRaw(this, &FPDAuthRegisterRequest::OnHttpResponse);
    
    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDAuthRegisterRequest::ToString()
{
    return FString::Printf(TEXT("FPDAuthRegisterRequest - Nickname: %s"), *RequestData.Nickname);
}

void FPDAuthRegisterRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }
    
    FJsonObjectConverter::JsonObjectStringToUStruct<FPDAuthRegisterResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Account created - PlayerId: %s"), *ResponseData.PlayerId);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
