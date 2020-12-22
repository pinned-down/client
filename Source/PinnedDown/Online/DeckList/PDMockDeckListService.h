#pragma once

#include "CoreMinimal.h"

#include "Online/DeckList/PDDeckListService.h"

#include "PDMockDeckListService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMockDeckListService : public UPDDeckListService
{
    GENERATED_BODY()

public:
    virtual void Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
};
