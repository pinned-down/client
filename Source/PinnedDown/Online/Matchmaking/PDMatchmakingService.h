#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Matchmaking/PDMatchmakingEnqueueRequest.h"

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

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UPROPERTY()
    UPDAuthService* AuthService;

    UFUNCTION()
    void OnEnqueueSuccess(const FPDMatchmakingEnqueueResponseData& Response);

    UFUNCTION()
    void OnEnqueueError(const FString& ErrorMessage);
};
