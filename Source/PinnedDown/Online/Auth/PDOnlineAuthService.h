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

    virtual void Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    virtual FString GetPlayerId() const override;

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UPROPERTY()
    FString PlayerId;

    UFUNCTION()
    void OnLoginSuccess(const FPDAuthLoginResponseData& Response);

    UFUNCTION()
    void OnLoginError(const FString& ErrorMessage);
};
