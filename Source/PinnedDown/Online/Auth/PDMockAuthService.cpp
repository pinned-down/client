#include "PDMockAuthService.h"

void UPDMockAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PlayerId = FGuid::NewGuid().ToString();

    FPDAuthLoginResponseData Response;
    OnSuccess.ExecuteIfBound(Response);
}

FString UPDMockAuthService::GetPlayerId() const
{
    return PlayerId;
}
