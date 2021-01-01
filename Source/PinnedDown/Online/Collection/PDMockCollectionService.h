#pragma once

#include "CoreMinimal.h"

#include "Online/Collection/PDCollectionService.h"

#include "PDMockCollectionService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMockCollectionService : public UPDCollectionService
{
    GENERATED_BODY()

public:
    virtual void Get(const FPDCollectionGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
};
