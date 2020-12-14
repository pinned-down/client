#pragma once

#include "CoreMinimal.h"

#include "Online/Matchmaking/PDMatchmakingService.h"

#include "PDMockMatchmakingService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMockMatchmakingService : public UPDMatchmakingService
{
    GENERATED_BODY()

public:
    void Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void Poll(const FPDMatchmakingPollSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
};
