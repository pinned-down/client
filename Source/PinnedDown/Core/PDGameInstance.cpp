#include "PDGameInstance.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/Auth/PDAuthService.h"

void UPDGameInstance::Init()
{
    Super::Init();

    // Create services.
    HttpRequestBuilder = NewObject<UPDOnlineHttpRequestBuilder>(this);

    AuthService = NewObject<UPDAuthService>(this);
    AuthService->Init(HttpRequestBuilder);
}

UPDAuthService* UPDGameInstance::GetAuthService() const
{
    return AuthService;
}

