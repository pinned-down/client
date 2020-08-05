#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Core/PDDelegate.h"
#include "Online/PDOnlineLog.h"
#include "Online/PDOnlineRequest.h"

#include "PDOnlineService.generated.h"

struct FPDOnlineRequest;

/** Provides common functionality for sending requests to remote endpoints. */
UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOnlineService : public UObject
{
    GENERATED_BODY()

protected:
    /** Adds the passed request to the request queue for processing. */
    template<typename RequestType, typename SuccessCallbackType>
    bool AddRequest(TSharedPtr<RequestType> Request, const SuccessCallbackType& OnSuccess, const SuccessCallbackType& OnServiceSuccess,
        const FPDOnlineErrorSignature& OnError, const FPDOnlineErrorSignature& OnServiceError)
    {
        if (!Request.IsValid())
        {
            return false;
        }

        // Set callbacks.
        Request->OnSuccess = OnSuccess;
        Request->OnServiceSuccess = OnServiceSuccess;
        Request->OnError = OnError;
        Request->OnServiceError = OnServiceError;

        // Enqueue request.
        PendingRequests.Add(Request);

        if (PendingRequests.Num() == 1)
        {
            ProcessRequestQueue();
        }

        return true;
    }

    template<typename RequestType, typename ResponseType>
    void OnPendingRequestSuccess(const ResponseType& Response)
    {
        TSharedPtr<RequestType> Request = StaticCastSharedPtr<RequestType>(GetCurrentPendingRequest());

        if (!Request.IsValid())
        {
            return;
        }

        UE_LOG(LogPDOnline, Log, TEXT("Sucessfully executed request."));

        Request->OnSuccess.ExecuteIfBound(Response);

        DequeueCurrentPendingRequest();
    }

    void OnPendingRequestError(const FString& ErrorMessage)
    {
        TSharedPtr<FPDOnlineRequest> Request = GetCurrentPendingRequest();

        if (!Request.IsValid())
        {
            return;
        }

        UE_LOG(LogPDOnline, Error, TEXT("Failed to execute request: %s"), *ErrorMessage);

        Request->OnError.ExecuteIfBound(ErrorMessage);

        DequeueCurrentPendingRequest();
    }

private:
    TArray<TSharedPtr<FPDOnlineRequest>> PendingRequests;

    /** Checks if there's any queued request, and executes it. */
    void ProcessRequestQueue();

    /** Removes the current pending request from the queue, and executes the next one, if any. */
    void DequeueCurrentPendingRequest();

    /** Gets the current in-flight request. */
    TSharedPtr<FPDOnlineRequest> GetCurrentPendingRequest() const;
};
