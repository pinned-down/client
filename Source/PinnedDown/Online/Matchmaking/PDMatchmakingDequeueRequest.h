#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Matchmaking/PDMatchmakingDequeueRequestData.h"
#include "Online/Matchmaking/PDMatchmakingDequeueResponseData.h"

#include "PDMatchmakingDequeueRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDMatchmakingDequeueSuccessSignature, const FPDMatchmakingDequeueResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDMatchmakingDequeueRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDMatchmakingDequeueRequestData RequestData;
    FPDMatchmakingDequeueResponseData ResponseData;

    FPDMatchmakingDequeueSuccessSignature OnSuccess;
    FPDMatchmakingDequeueSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
