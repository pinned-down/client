#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Matchmaking/PDMatchmakingEnqueueRequest.h"
#include "Online/Matchmaking/PDMatchmakingDequeueRequest.h"
#include "Online/Matchmaking/PDMatchmakingPollRequest.h"

#include "PDMatchmakingService.generated.h"

class UPDAuthService;
class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMatchmakingService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder, UPDAuthService* InAuthService);

    UFUNCTION(BlueprintCallable)
    void Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    void Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    void Poll(const FPDMatchmakingPollSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UPROPERTY()
    UPDAuthService* AuthService;

    UFUNCTION()
    void OnEnqueueSuccess(const FPDMatchmakingEnqueueResponseData& Response);

    UFUNCTION()
    void OnEnqueueError(const FString& ErrorMessage);

    UFUNCTION()
    void OnDequeueSuccess(const FPDMatchmakingDequeueResponseData& Response);

    UFUNCTION()
    void OnDequeueError(const FString& ErrorMessage);

    UFUNCTION()
    void OnPollSuccess(const FPDMatchmakingPollResponseData& Response);

    UFUNCTION()
    void OnPollError(const FString& ErrorMessage);
};
