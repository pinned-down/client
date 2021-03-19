#pragma once

#include "CoreMinimal.h"

#include "Online/Collection/PDCollectionService.h"

#include "PDOnlineCollectionService.generated.h"

class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOnlineCollectionService : public UPDCollectionService
{
    GENERATED_BODY()

public:
    void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder);

    void Get(const FPDCollectionGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void Claim(const FPDCollectionClaimSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void OpenCardPack(const FString& ItemDefinitionId, const FPDCollectionOpenCardPackSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UFUNCTION()
    void OnGetSuccess(const FPDCollectionGetResponseData& Response);

    UFUNCTION()
    void OnGetError(const FString& ErrorMessage);

    UFUNCTION()
    void OnClaimSuccess(const FPDCollectionClaimResponseData& Response);

    UFUNCTION()
    void OnClaimError(const FString& ErrorMessage);

    UFUNCTION()
    void OnOpenCardPackSuccess(const FPDCollectionOpenCardPackResponseData& Response);

    UFUNCTION()
    void OnOpenCardPackError(const FString& ErrorMessage);
};
