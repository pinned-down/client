#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDOnlineService.generated.h"

class FPDOnlineRequest;

/** Provides common functionality for sending requests to remote endpoints. */
UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOnlineService : public UObject
{
    GENERATED_BODY()

protected:
    /** Adds the passed request to the request queue for processing. */
    bool AddRequest(TSharedPtr<FPDOnlineRequest> Request);

private:
    TArray<TSharedPtr<FPDOnlineRequest>> PendingRequests;

    /** Checks if there's any queued request, and executes it. */
    void ProcessRequestQueue();

    /** Removes the current pending request from the queue, and executes the next one, if any. */
    void DequeueCurrentPendingRequest();

    UFUNCTION()
    void OnPendingRequestSuccess();

    UFUNCTION()
    void OnPendingRequestError(const FString& ErrorMessage);

    /** Gets the current in-flight request. */
    TSharedPtr<FPDOnlineRequest> GetCurrentPendingRequest() const;
};
