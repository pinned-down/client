#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Matchmaking/PDMatchmakingPollRequestData.h"
#include "Online/Matchmaking/PDMatchmakingPollResponseData.h"

#include "PDMatchmakingPollRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDMatchmakingPollSuccessSignature, const FPDMatchmakingPollResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDMatchmakingPollRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDMatchmakingPollRequestData RequestData;
    FPDMatchmakingPollResponseData ResponseData;

    FPDMatchmakingPollSuccessSignature OnSuccess;
    FPDMatchmakingPollSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
