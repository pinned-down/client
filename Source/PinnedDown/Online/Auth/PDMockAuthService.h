#pragma once

#include "CoreMinimal.h"

#include "Online/Auth/PDAuthService.h"

#include "PDMockAuthService.generated.h"

UCLASS(BlueprintType, Config = Game)
class PINNEDDOWN_API UPDMockAuthService : public UPDAuthService
{
    GENERATED_BODY()

public:
    virtual void Register(const FPDAuthRegisterRequestData& RequestData, const FPDAuthRegisterSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    virtual void Login(const FPDAuthLoginSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    virtual FString GetPlayerId() const override;

private:
    FString PlayerId;
};
