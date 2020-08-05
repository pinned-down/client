#include "PDGameInstance.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/Auth/PDAuthService.h"
#include "Online/Matchmaking/PDMatchmakingService.h"

void UPDGameInstance::Init()
{
    Super::Init();

    // Create services.
    HttpRequestBuilder = NewObject<UPDOnlineHttpRequestBuilder>(this);

    AuthService = NewObject<UPDAuthService>(this);
    AuthService->Init(HttpRequestBuilder);

    MatchmakingService = NewObject<UPDMatchmakingService>(this);
    MatchmakingService->Init(HttpRequestBuilder, AuthService);
}

UPDAuthService* UPDGameInstance::GetAuthService() const
{
    return AuthService;
}

UPDMatchmakingService* UPDGameInstance::GetMatchmakingService() const
{
    return MatchmakingService;
}
