#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Collection/PDCollectionGetRequest.h"

#include "PDCollectionService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDCollectionService : public UPDOnlineService
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual void Get(const FPDCollectionGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);
};
