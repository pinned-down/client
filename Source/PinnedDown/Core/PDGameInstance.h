#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "PDGameInstance.generated.h"

class UPDAuthService;

UCLASS()
class PINNEDDOWN_API UPDGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintPure)
    UPDAuthService* GetAuthService() const;

private:
    UPROPERTY()
    UPDAuthService* AuthService;
};
