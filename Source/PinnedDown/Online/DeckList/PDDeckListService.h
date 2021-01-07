#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/DeckList/PDDeckListGetRequest.h"
#include "Online/DeckList/PDDeckListPutRequest.h"

#include "PDDeckListService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDDeckListService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual void Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

    UFUNCTION(BlueprintCallable)
    virtual void Put(const FPDDeckListPutRequestData& RequestData, const FPDDeckListPutSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);
};
