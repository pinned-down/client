#include "PDOnlineService.h"

#include "PDOnlineLog.h"
#include "PDOnlineRequest.h"

void UPDOnlineService::ProcessRequestQueue()
{
    TSharedPtr<FPDOnlineRequest> Request = GetCurrentPendingRequest();

    if (!Request.IsValid())
    {
        return;
    }

    // Execute request.
    UE_LOG(LogPDOnline, Log, TEXT("Executing request: %s"), *Request->ToString());

    Request->Execute();
}

void UPDOnlineService::DequeueCurrentPendingRequest()
{
    TSharedPtr<FPDOnlineRequest> Request = GetCurrentPendingRequest();

    if (!Request.IsValid())
    {
        return;
    }

    // Remove request.
    PendingRequests.RemoveAt(0);

    // Check if there's anything left to do.
    if (PendingRequests.Num() > 0)
    {
        ProcessRequestQueue();
    }
}

TSharedPtr<FPDOnlineRequest> UPDOnlineService::GetCurrentPendingRequest() const
{
    return PendingRequests.Num() > 0 ? PendingRequests[0] : TSharedPtr<FPDOnlineRequest>();
}
