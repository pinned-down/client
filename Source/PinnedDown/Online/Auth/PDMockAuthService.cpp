#include "PDMockAuthService.h"

void UPDMockAuthService::Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PlayerId = RequestData.Nickname;

    FPDAuthRegisterResponseData Response;
    Response.PlayerId = PlayerId;

    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDAuthLoginResponseData Response;
    OnSuccess.ExecuteIfBound(Response);
}

FString UPDMockAuthService::GetPlayerId() const
{
    return PlayerId;
}
