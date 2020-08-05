#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/PDOnlineError.h"

#include "PDOnlineRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDOnlineErrorSignature, const FString&, ErrorMessage);

/** Request to send to a remote endpoint. */
USTRUCT()
struct PINNEDDOWN_API FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDOnlineError Error;

    FPDOnlineRequest();
    virtual ~FPDOnlineRequest();

    /** Prepares and sends the request to the remote endpoint. */
    virtual void Execute();

    /** Gets a textual description of this request. */
    virtual FString ToString();

    /** Event when this request failed to execute. */
    FPDOnlineErrorSignature OnError;
    FPDOnlineErrorSignature OnServiceError;

protected:
    bool CheckForErrors(FHttpResponsePtr Response, bool bWasSuccessful);
};
