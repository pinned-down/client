#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Auth/PDAuthRegisterRequest.h"
#include "Online/Auth/PDAuthLoginRequest.h"

#include "PDAuthService.generated.h"

UCLASS(BlueprintType, Config = Game)
class PINNEDDOWN_API UPDAuthService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual void Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    virtual void Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintPure)
    virtual FString GetPlayerId() const;
};
