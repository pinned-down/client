#include "PDGameInstance.h"

#include "Engine/DataTable.h"

#include "Core/PDLog.h"
#include "Data/PDCardSet.h"
#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/Auth/PDOnlineAuthService.h"
#include "Online/Matchmaking/PDMatchmakingService.h"

void UPDGameInstance::Init()
{
    Super::Init();

    // Create services.
    if (bMockBackend)
    {
        UE_LOG(LogPD, Log, TEXT("Using mock backend."));
    }
    else
    {
        HttpRequestBuilder = NewObject<UPDOnlineHttpRequestBuilder>(this);

        UPDOnlineAuthService* OnlineAuthService = NewObject<UPDOnlineAuthService>(this);
        OnlineAuthService->Init(HttpRequestBuilder);
        AuthService = OnlineAuthService;

        MatchmakingService = NewObject<UPDMatchmakingService>(this);
        MatchmakingService->Init(HttpRequestBuilder, AuthService);
    }
    
    // Load data.
    CardSet = NewObject<UPDCardSet>(this);
    CardSet->LoadFromDisk();

    UE_LOG(LogPD, Log, TEXT("Loaded card set with %i cards and abilities."), CardSet->Num());

    if (IsValid(CardMetadata))
    {
        UE_LOG(LogPD, Log, TEXT("Loaded card metadata for %i cards."), CardMetadata->GetRowNames().Num());

        // Validate data.
        TArray<FName> CardSetIds = CardSet->GetCardIds();
        TArray<FName> CardMetadataIds = CardMetadata->GetRowNames();

        for (const FName& CardId : CardMetadataIds)
        {
            if (!CardSetIds.Contains(CardId))
            {
                UE_LOG(LogPD, Warning, TEXT("Card %s not found in card data."), *CardId.ToString());
            }
        }
    }
    else
    {
        UE_LOG(LogPD, Warning, TEXT("Card metadata table not set for %s."), *GetName());
    }
}

UPDAuthService* UPDGameInstance::GetAuthService() const
{
    return AuthService;
}

UPDCardSet* UPDGameInstance::GetCardSet() const
{
    return CardSet;
}

UDataTable* UPDGameInstance::GetCardMetadata() const
{
    return CardMetadata;
}

UPDMatchmakingService* UPDGameInstance::GetMatchmakingService() const
{
    return MatchmakingService;
}
