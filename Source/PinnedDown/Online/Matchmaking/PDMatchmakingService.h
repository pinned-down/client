#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Matchmaking/PDMatchmakingEnqueueRequest.h"
#include "Online/Matchmaking/PDMatchmakingDequeueRequest.h"
#include "Online/Matchmaking/PDMatchmakingPollRequest.h"

#include "PDMatchmakingService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMatchmakingService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual void Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    virtual void Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    virtual void Poll(const FPDMatchmakingPollSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);
};
