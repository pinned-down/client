#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/DeckList/PDDeckListPutRequestData.h"

#include "PDDeckListPutRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE(FPDDeckListPutSuccessSignature);

USTRUCT()
struct PINNEDDOWN_API FPDDeckListPutRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    int64 LoadoutId;
    FPDDeckListPutRequestData RequestData;

    FPDDeckListPutSuccessSignature OnSuccess;
    FPDDeckListPutSuccessSignature OnServiceSuccess;

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
