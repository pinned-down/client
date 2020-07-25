#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

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
    bool AddRequest(TSharedPtr<FPDOnlineRequest> Request);

    template<typename RequestType, typename SuccessCallbackType>
    bool AddRequestWithCallbacks(TSharedPtr<RequestType> Request,
        const SuccessCallbackType& OnSuccess, const SuccessCallbackType& OnServiceSuccess,
        const FPDOnlineErrorSignature& OnError, const FPDOnlineErrorSignature& OnServiceError)
    {
        Request->OnSuccess.Add(OnServiceSuccess);
        Request->OnSuccess.Add(OnSuccess);
        Request->OnError.Add(OnServiceError);
        Request->OnError.Add(OnError);

        return AddRequest(Request);
    }

    UFUNCTION()
    void OnPendingRequestSuccess();

    UFUNCTION()
    void OnPendingRequestError(const FString& ErrorMessage);

private:
    TArray<TSharedPtr<FPDOnlineRequest>> PendingRequests;

    /** Checks if there's any queued request, and executes it. */
    void ProcessRequestQueue();

    /** Removes the current pending request from the queue, and executes the next one, if any. */
    void DequeueCurrentPendingRequest();

    /** Gets the current in-flight request. */
    TSharedPtr<FPDOnlineRequest> GetCurrentPendingRequest() const;
};
