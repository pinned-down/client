#include "PDAuthService.h"

void UPDAuthService::Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthRegisterSuccessSignature, OnServiceSuccess, &UPDAuthService::OnRegisterSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDAuthService::OnPendingRequestError);

    TSharedPtr<FPDAuthRegisterRequest> Request = MakeShared<FPDAuthRegisterRequest>();
    Request->RequestData = RequestData;

    AddRequestWithCallbacks(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDAuthService::Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDAuthLoginSuccessSignature, OnServiceSuccess, &UPDAuthService::OnLoginSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDAuthService::OnPendingRequestError);

    TSharedPtr<FPDAuthLoginRequest> Request = MakeShared<FPDAuthLoginRequest>();
    Request->RequestData = FPDAuthLoginRequestData(PlayerId);
    
    AddRequestWithCallbacks(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDAuthService::OnRegisterSuccess(const FPDAuthRegisterResponseData& Response)
{
    PlayerId = Response.PlayerId;

    OnPendingRequestSuccess();
}

void UPDAuthService::OnLoginSuccess(const FPDAuthLoginResponseData& Response)
{
    OnPendingRequestSuccess();
}
