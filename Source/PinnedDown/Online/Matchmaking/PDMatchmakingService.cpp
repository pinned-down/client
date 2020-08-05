#include "PDMatchmakingService.h"

#include "Online/Auth/PDAuthService.h"

void UPDMatchmakingService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder, UPDAuthService* InAuthService)
{
    HttpRequestBuilder = InHttpRequestBuilder;
    AuthService = InAuthService;
}

void UPDMatchmakingService::Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDMatchmakingEnqueueSuccessSignature, OnServiceSuccess, &UPDMatchmakingService::OnEnqueueSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDMatchmakingService::OnEnqueueError);

    TSharedPtr<FPDMatchmakingEnqueueRequest> Request = MakeShared<FPDMatchmakingEnqueueRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData = RequestData;

    if (Request->RequestData.PlayerId.IsEmpty())
    {
        Request->RequestData.PlayerId = AuthService->GetPlayerId();
    }

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDMatchmakingService::Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDMatchmakingDequeueSuccessSignature, OnServiceSuccess, &UPDMatchmakingService::OnDequeueSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDMatchmakingService::OnDequeueError);

    TSharedPtr<FPDMatchmakingDequeueRequest> Request = MakeShared<FPDMatchmakingDequeueRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData.PlayerId = AuthService->GetPlayerId();

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDMatchmakingService::OnEnqueueSuccess(const FPDMatchmakingEnqueueResponseData& Response)
{
    OnPendingRequestSuccess<FPDMatchmakingEnqueueRequest, FPDMatchmakingEnqueueResponseData>(Response);
}

void UPDMatchmakingService::OnEnqueueError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}

void UPDMatchmakingService::OnDequeueSuccess(const FPDMatchmakingDequeueResponseData& Response)
{
    OnPendingRequestSuccess<FPDMatchmakingDequeueRequest, FPDMatchmakingDequeueResponseData>(Response);
}

void UPDMatchmakingService::OnDequeueError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
