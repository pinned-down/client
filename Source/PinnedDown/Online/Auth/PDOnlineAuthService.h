#pragma once

#include "CoreMinimal.h"

#include "Online/Auth/PDAuthService.h"

#include "PDOnlineAuthService.generated.h"

class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType, Config = Game)
class PINNEDDOWN_API UPDOnlineAuthService : public UPDAuthService
{
    GENERATED_BODY()

public:
    void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder);

    virtual void Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    virtual void Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    virtual FString GetPlayerId() const override;

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
