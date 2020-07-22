#include "PDOnlineService.h"

#include "PDOnlineLog.h"
#include "PDOnlineRequest.h"

bool UPDOnlineService::AddRequest(TSharedPtr<FPDOnlineRequest> Request)
{
    if (!Request.IsValid())
    {
        return false;
    }

    // Enqueue request.
    PendingRequests.Add(Request);

    if (PendingRequests.Num() == 1)
    {
        ProcessRequestQueue();
    }

    return true;
}

void UPDOnlineService::ProcessRequestQueue()
{
    TSharedPtr<FPDOnlineRequest> Request = GetCurrentPendingRequest();

    if (!Request.IsValid())
    {
        return;
    }

    // Register callbacks.
    Request->OnSuccess.BindUObject(this, &UPDOnlineService::OnPendingRequestSuccess);
    Request->OnError.BindUObject(this, &UPDOnlineService::OnPendingRequestError);

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

    // Clear callbacks.
    Request->OnSuccess.Unbind();
    Request->OnError.Unbind();

    // Remove request.
    PendingRequests.RemoveAt(0);

    // Check if there's anything left to do.
    if (PendingRequests.Num() > 0)
    {
        ProcessRequestQueue();
    }
}

void UPDOnlineService::OnPendingRequestSuccess()
{
    TSharedPtr<FPDOnlineRequest> Request = GetCurrentPendingRequest();

    if (!Request.IsValid())
    {
        return;
    }

    UE_LOG(LogPDOnline, Log, TEXT("Sucessfully executed request."));

    DequeueCurrentPendingRequest();
}

void UPDOnlineService::OnPendingRequestError(const FString& ErrorMessage)
{
    TSharedPtr<FPDOnlineRequest> Request = GetCurrentPendingRequest();

    if (!Request.IsValid())
    {
        return;
    }

    UE_LOG(LogPDOnline, Error, TEXT("Failed to execute request: %s"), *ErrorMessage);

    DequeueCurrentPendingRequest();
}

TSharedPtr<FPDOnlineRequest> UPDOnlineService::GetCurrentPendingRequest() const
{
    return PendingRequests.Num() > 0 ? PendingRequests[0] : TSharedPtr<FPDOnlineRequest>();
}
