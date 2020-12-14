#include "PDMockMatchmakingService.h"

void UPDMockMatchmakingService::Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDMatchmakingEnqueueResponseData Response;
    Response.Status = TEXT("QUEUED");
    
    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockMatchmakingService::Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDMatchmakingDequeueResponseData Response;

    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockMatchmakingService::Poll(const FPDMatchmakingPollSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDMatchmakingPollResponseData Response;
    Response.Status = TEXT("WAITING_FOR_PLAYERS");

    OnSuccess.ExecuteIfBound(Response);
}
