#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Collection/PDCollectionGetResponseData.h"

#include "PDCollectionGetRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDCollectionGetSuccessSignature, const FPDCollectionGetResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDCollectionGetRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDCollectionGetResponseData ResponseData;

    FPDCollectionGetSuccessSignature OnSuccess;
    FPDCollectionGetSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
