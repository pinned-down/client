#pragma once

#include "CoreMinimal.h"

#include "Online/Matchmaking/PDMatchmakingService.h"

#include "PDOnlineMatchmakingService.generated.h"

class UPDAuthService;
class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOnlineMatchmakingService : public UPDMatchmakingService
{
    GENERATED_BODY()

public:
    void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder, UPDAuthService* InAuthService);

    void Enqueue(const FPDMatchmakingEnqueueRequestData& RequestData, const FPDMatchmakingEnqueueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void Dequeue(const FPDMatchmakingDequeueSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void Poll(const FPDMatchmakingPollSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;

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
