#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Collection/PDCollectionClaimResponseData.h"

#include "PDCollectionClaimRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDCollectionClaimSuccessSignature, const FPDCollectionClaimResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDCollectionClaimRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDCollectionClaimResponseData ResponseData;

    FPDCollectionClaimSuccessSignature OnSuccess;
    FPDCollectionClaimSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
