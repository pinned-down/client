#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Auth/PDAuthLoginRequestData.h"
#include "Online/Auth/PDAuthLoginResponseData.h"

#include "PDAuthLoginRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDAuthLoginSuccessSignature, const FPDAuthLoginResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDAuthLoginRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDAuthLoginRequestData RequestData;
    FPDAuthLoginResponseData ResponseData;

    PDDeclareDynamicMulticastDelegate(FPDAuthLoginSuccessSignature, OnSuccess);

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
