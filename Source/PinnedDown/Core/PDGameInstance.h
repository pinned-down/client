#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "PDGameInstance.generated.h"

class UDataTable;

class UPDAuthService;
class UPDCardSet;
class UPDDeckListService;
class UPDMatchmakingService;
class UPDOnlineHttpRequestBuilder;

UCLASS(Config = Game)
class PINNEDDOWN_API UPDGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintPure)
    UPDAuthService* GetAuthService() const;

    UFUNCTION(BlueprintPure)
    UPDCardSet* GetCardSet() const;

    UFUNCTION(BlueprintPure)
    UDataTable* GetCardMetadata() const;

    UFUNCTION(BlueprintPure)
    UPDDeckListService* GetDeckListService() const;

    UFUNCTION(BlueprintPure)
    UPDMatchmakingService* GetMatchmakingService() const;

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UPROPERTY(Config)
    bool bMockBackend;

    UPROPERTY()
    UPDAuthService* AuthService;

    UPROPERTY()
    UPDDeckListService* DeckListService;

    UPROPERTY()
    UPDMatchmakingService* MatchmakingService;

    UPROPERTY()
    UPDCardSet* CardSet;

    UPROPERTY(EditDefaultsOnly)
    UDataTable* CardMetadata;
};
