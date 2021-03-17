#pragma once

#include "CoreMinimal.h"

#include "Online/DeckList/PDDeckListService.h"

#include "PDOnlineDeckListService.generated.h"

class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOnlineDeckListService : public UPDDeckListService
{
    GENERATED_BODY()

public:
    void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder);

    void Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
    void Put(int64 LoadoutId, const FPDDeckListPutRequestData& RequestData, const FPDDeckListPutSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;

private:
    UPROPERTY()
    UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

    UFUNCTION()
    void OnGetSuccess(const FPDDeckListGetResponseData& Response);

    UFUNCTION()
    void OnGetError(const FString& ErrorMessage);

    UFUNCTION()
    void OnPutSuccess();

    UFUNCTION()
    void OnPutError(const FString& ErrorMessage);
};
