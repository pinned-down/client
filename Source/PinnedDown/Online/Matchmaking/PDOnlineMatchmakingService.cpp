#include "PDOnlineMatchmakingService.h"

#include "Online/Auth/PDAuthService.h"

void UPDOnlineMatchmakingService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder, UPDAuthService* InAuthService)
{
    HttpRequestBuilder = InHttpRequestBuilder;
    AuthService = InAuthService;
}

void UPDOnlineMatchmakingService::Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDMatchmakingEnqueueSuccessSignature, OnServiceSuccess, &UPDOnlineMatchmakingService::OnEnqueueSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineMatchmakingService::OnEnqueueError);

    TSharedPtr<FPDMatchmakingEnqueueRequest> Request = MakeShared<FPDMatchmakingEnqueueRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData = RequestData;

    if (Request->RequestData.PlayerId.IsEmpty())
    {
        Request->RequestData.PlayerId = AuthService->GetPlayerId();
    }

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineMatchmakingService::Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDMatchmakingDequeueSuccessSignature, OnServiceSuccess, &UPDOnlineMatchmakingService::OnDequeueSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineMatchmakingService::OnDequeueError);

    TSharedPtr<FPDMatchmakingDequeueRequest> Request = MakeShared<FPDMatchmakingDequeueRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData.PlayerId = AuthService->GetPlayerId();

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineMatchmakingService::Poll(const FPDMatchmakingPollSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDMatchmakingPollSuccessSignature, OnServiceSuccess, &UPDOnlineMatchmakingService::OnPollSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineMatchmakingService::OnPollError);

    TSharedPtr<FPDMatchmakingPollRequest> Request = MakeShared<FPDMatchmakingPollRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->RequestData.PlayerId = AuthService->GetPlayerId();

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineMatchmakingService::OnEnqueueSuccess(const FPDMatchmakingEnqueueResponseData& Response)
{
    OnPendingRequestSuccess<FPDMatchmakingEnqueueRequest, FPDMatchmakingEnqueueResponseData>(Response);
}

void UPDOnlineMatchmakingService::OnEnqueueError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}

void UPDOnlineMatchmakingService::OnDequeueSuccess(const FPDMatchmakingDequeueResponseData& Response)
{
    OnPendingRequestSuccess<FPDMatchmakingDequeueRequest, FPDMatchmakingDequeueResponseData>(Response);
}

void UPDOnlineMatchmakingService::OnDequeueError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}

void UPDOnlineMatchmakingService::OnPollSuccess(const FPDMatchmakingPollResponseData& Response)
{
    OnPendingRequestSuccess<FPDMatchmakingPollRequest, FPDMatchmakingPollResponseData>(Response);
}

void UPDOnlineMatchmakingService::OnPollError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
