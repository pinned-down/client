#include "PDAuthService.h"

void UPDAuthService::Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
}

void UPDAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
}

FString UPDAuthService::GetPlayerId() const
{
    return FString();
}
