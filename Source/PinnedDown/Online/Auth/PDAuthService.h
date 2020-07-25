#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Auth/PDAuthRegisterRequest.h"
#include "Online/Auth/PDAuthLoginRequest.h"

#include "PDAuthService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAuthService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    void Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

private:
    FString PlayerId;

    UFUNCTION()
    void OnRegisterSuccess(const FPDAuthRegisterResponseData& Response);

    UFUNCTION()
    void OnLoginSuccess(const FPDAuthLoginResponseData& Response);
};
