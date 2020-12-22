#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/DeckList/PDDeckListGetResponseData.h"

#include "PDDeckListGetRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDDeckListGetSuccessSignature, const FPDDeckListGetResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDDeckListGetRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDDeckListGetResponseData ResponseData;

    FPDDeckListGetSuccessSignature OnSuccess;
    FPDDeckListGetSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
