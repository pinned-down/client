#include "PDAuthService.h"

#include "Online/PDOnlineHttpRequestBuilder.h"

void UPDAuthService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder)
{
    HttpRequestBuilder = InHttpRequestBuilder;
}

void UPDAuthService::Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthRegisterSuccessSignature, OnServiceSuccess, &UPDAuthService::OnRegisterSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDAuthService::OnRegisterError);

    TSharedPtr<FPDAuthRegisterRequest> Request = MakeShared<FPDAuthRegisterRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData = RequestData;

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthLoginSuccessSignature, OnServiceSuccess, &UPDAuthService::OnLoginSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDAuthService::OnLoginError);

    TSharedPtr<FPDAuthLoginRequest> Request = MakeShared<FPDAuthLoginRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData = FPDAuthLoginRequestData(PlayerId);
    
    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

FString UPDAuthService::GetPlayerId() const
{
    return PlayerId;
}

void UPDAuthService::OnRegisterSuccess(const FPDAuthRegisterResponseData& Response)
{
    // Store player id.
    PlayerId = Response.PlayerId;

    SaveConfig();

    OnPendingRequestSuccess<FPDAuthRegisterRequest, FPDAuthRegisterResponseData>(Response);
}

void UPDAuthService::OnRegisterError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}

void UPDAuthService::OnLoginSuccess(const FPDAuthLoginResponseData& Response)
{
    // Store auth token.
    HttpRequestBuilder->Authorization = TEXT("Bearer ") + Response.Token;

    OnPendingRequestSuccess<FPDAuthLoginRequest, FPDAuthLoginResponseData>(Response);
}

void UPDAuthService::OnLoginError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
