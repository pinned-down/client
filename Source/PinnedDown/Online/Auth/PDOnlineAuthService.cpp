#include "PDOnlineAuthService.h"

#include "Online/PDOnlineHttpRequestBuilder.h"

void UPDOnlineAuthService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder)
{
    HttpRequestBuilder = InHttpRequestBuilder;
}

void UPDOnlineAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthLoginSuccessSignature, OnServiceSuccess, &UPDOnlineAuthService::OnLoginSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineAuthService::OnLoginError);

    TSharedPtr<FPDAuthLoginRequest> Request = MakeShared<FPDAuthLoginRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;

    // TODO(np): Get from OAuth provider (e.g. Steam).
    Request->RequestData.Provider = TEXT("");
    Request->RequestData.Key = FGuid::NewGuid().ToString();
    Request->RequestData.Context = TEXT("");
    Request->RequestData.Role = TEXT("ROLE_USER");

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

FString UPDOnlineAuthService::GetPlayerId() const
{
    return PlayerId;
}

void UPDOnlineAuthService::OnLoginSuccess(const FPDAuthLoginResponseData& Response)
{
    // Store player id.
    PlayerId = Response.ProviderUserId;

    // Store auth token.
    HttpRequestBuilder->Authorization = TEXT("Bearer ") + Response.Token;

    OnPendingRequestSuccess<FPDAuthLoginRequest, FPDAuthLoginResponseData>(Response);
}

void UPDOnlineAuthService::OnLoginError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
