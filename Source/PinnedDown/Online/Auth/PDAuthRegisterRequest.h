#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Core/PDDelegate.h"
#include "Online/Auth/PDAuthRegisterRequestData.h"
#include "Online/Auth/PDAuthRegisterResponseData.h"

#include "PDAuthRegisterRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDAuthRegisterSuccessSignature, const FPDAuthRegisterResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDAuthRegisterRequest : public FPDOnlineRequest
{
    GENERATED_BODY()

public:
    FPDAuthRegisterRequestData RequestData;
    FPDAuthRegisterResponseData ResponseData;

    PDDeclareDynamicMulticastDelegate(FPDAuthRegisterSuccessSignature, OnSuccess);

    virtual void Execute() override;
    virtual FString ToString() override;

private:
    void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
