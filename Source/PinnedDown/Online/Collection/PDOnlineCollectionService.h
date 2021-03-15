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

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UFUNCTION()
    void OnGetSuccess(const FPDCollectionGetResponseData& Response);

    UFUNCTION()
    void OnGetError(const FString& ErrorMessage);
};
