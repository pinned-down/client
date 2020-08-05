#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Auth/PDAuthRegisterRequest.h"
#include "Online/Auth/PDAuthLoginRequest.h"

#include "PDAuthService.generated.h"

class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType, Config=Game)
class PINNEDDOWN_API UPDAuthService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder);

    UFUNCTION(BlueprintCallable)
    void Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    void Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintPure)
    FString GetPlayerId() const;

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UPROPERTY(Config)
    FString PlayerId;

    UFUNCTION()
    void OnRegisterSuccess(const FPDAuthRegisterResponseData& Response);

    UFUNCTION()
    void OnRegisterError(const FString& ErrorMessage);

    UFUNCTION()
    void OnLoginSuccess(const FPDAuthLoginResponseData& Response);

    UFUNCTION()
    void OnLoginError(const FString& ErrorMessage);
};
