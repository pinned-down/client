#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "PDGameInstance.generated.h"

class UPDAuthService;
class UPDMatchmakingService;
class UPDOnlineHttpRequestBuilder;

UCLASS()
class PINNEDDOWN_API UPDGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintPure)
    UPDAuthService* GetAuthService() const;

    UFUNCTION(BlueprintPure)
    UPDMatchmakingService* GetMatchmakingService() const;

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UPROPERTY()
    UPDAuthService* AuthService;

    UPROPERTY()
    UPDMatchmakingService* MatchmakingService;
};
