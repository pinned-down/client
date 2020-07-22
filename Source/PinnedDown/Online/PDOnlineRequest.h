#pragma once

#include "CoreMinimal.h"

DECLARE_DELEGATE(FPDOnlineRequestSuccessSignature);
DECLARE_DELEGATE_OneParam(FPDOnlineRequestErrorSignature, const FString& /*ErrorMessage*/);

/** Request to send to a remote endpoint. */
class PINNEDDOWN_API FPDOnlineRequest
{
public:
    FPDOnlineRequest();
    virtual ~FPDOnlineRequest();

    /** Prepares and sends the request to the remote endpoint. */
    virtual void Execute() = 0;

    /** Gets a textual description of this request. */
    virtual FString ToString() = 0;

    /** Event when this request was successfully executed. */
    FPDOnlineRequestSuccessSignature OnSuccess;

    /** Event when this request failed to execute. */
    FPDOnlineRequestErrorSignature OnError;
};
