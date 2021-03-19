#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Collection/PDCollectionOpenCardPackResponseData.h"

#include "PDCollectionOpenCardPackRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDCollectionOpenCardPackSuccessSignature, const FPDCollectionOpenCardPackResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDCollectionOpenCardPackRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FString ItemDefinitionId;
    FPDCollectionOpenCardPackResponseData ResponseData;

    FPDCollectionOpenCardPackSuccessSignature OnSuccess;
    FPDCollectionOpenCardPackSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
