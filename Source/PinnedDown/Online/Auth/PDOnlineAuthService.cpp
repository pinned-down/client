#include "PDOnlineAuthService.h"

#include "Online/PDOnlineHttpRequestBuilder.h"

void UPDOnlineAuthService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder)
{
    HttpRequestBuilder = InHttpRequestBuilder;
}

void UPDOnlineAuthService::Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthRegisterSuccessSignature, OnServiceSuccess, &UPDOnlineAuthService::OnRegisterSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineAuthService::OnRegisterError);

    TSharedPtr<FPDAuthRegisterRequest> Request = MakeShared<FPDAuthRegisterRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData = RequestData;

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthLoginSuccessSignature, OnServiceSuccess, &UPDOnlineAuthService::OnLoginSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineAuthService::OnLoginError);

    TSharedPtr<FPDAuthLoginRequest> Request = MakeShared<FPDAuthLoginRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData = FPDAuthLoginRequestData(PlayerId);
    
    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

FString UPDOnlineAuthService::GetPlayerId() const
{
    return PlayerId;
}

void UPDOnlineAuthService::OnRegisterSuccess(const FPDAuthRegisterResponseData& Response)
{
    // Store player id.
    PlayerId = Response.PlayerId;

    SaveConfig();

    OnPendingRequestSuccess<FPDAuthRegisterRequest, FPDAuthRegisterResponseData>(Response);
}

void UPDOnlineAuthService::OnRegisterError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}

void UPDOnlineAuthService::OnLoginSuccess(const FPDAuthLoginResponseData& Response)
{
    // Store auth token.
    HttpRequestBuilder->Authorization = TEXT("Bearer ") + Response.Token;

    OnPendingRequestSuccess<FPDAuthLoginRequest, FPDAuthLoginResponseData>(Response);
}

void UPDOnlineAuthService::OnLoginError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
