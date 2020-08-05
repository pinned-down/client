#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Matchmaking/PDMatchmakingEnqueueRequestData.h"
#include "Online/Matchmaking/PDMatchmakingEnqueueResponseData.h"

#include "PDMatchmakingEnqueueRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDMatchmakingEnqueueSuccessSignature, const FPDMatchmakingEnqueueResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDMatchmakingEnqueueRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDMatchmakingEnqueueRequestData RequestData;
    FPDMatchmakingEnqueueResponseData ResponseData;

    FPDMatchmakingEnqueueSuccessSignature OnSuccess;
    FPDMatchmakingEnqueueSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
