#include "PDGameInstance.h"

#include "Online/Auth/PDAuthService.h"

void UPDGameInstance::Init()
{
    Super::Init();

    // Create services.
    AuthService = NewObject<UPDAuthService>(this);
}

UPDAuthService* UPDGameInstance::GetAuthService() const
{
    return AuthService;
}

