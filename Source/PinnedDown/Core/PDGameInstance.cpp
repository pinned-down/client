#include "PDGameInstance.h"

#include "Engine/DataTable.h"

#include "Core/PDLog.h"
#include "Data/PDCardSet.h"
#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/Auth/PDMockAuthService.h"
#include "Online/Auth/PDOnlineAuthService.h"
#include "Online/Collection/PDMockCollectionService.h"
#include "Online/Collection/PDOnlineCollectionService.h"
#include "Online/DeckList/PDMockDeckListService.h"
#include "Online/DeckList/PDOnlineDeckListService.h"
#include "Online/Matchmaking/PDMockMatchmakingService.h"
#include "Online/Matchmaking/PDOnlineMatchmakingService.h"
#include "Online/Quests/PDMockQuestService.h"
#include "Online/Quests/PDOnlineQuestService.h"

void UPDGameInstance::Init()
{
    Super::Init();

    // Create services.
    if (bMockBackend)
    {
        UE_LOG(LogPD, Log, TEXT("Using mock backend."));

        AuthService = NewObject<UPDMockAuthService>(this);
        MatchmakingService = NewObject<UPDMockMatchmakingService>(this);
        CollectionService = NewObject<UPDMockCollectionService>(this);
        DeckListService = NewObject<UPDMockDeckListService>(this);
        QuestService = NewObject<UPDMockQuestService>(this);
    }
    else
    {
        HttpRequestBuilder = NewObject<UPDOnlineHttpRequestBuilder>(this);

        UPDOnlineAuthService* OnlineAuthService = NewObject<UPDOnlineAuthService>(this);
        OnlineAuthService->Init(HttpRequestBuilder);
        AuthService = OnlineAuthService;

        UPDOnlineMatchmakingService* OnlineMatchmakingService = NewObject<UPDOnlineMatchmakingService>(this);
        OnlineMatchmakingService->Init(HttpRequestBuilder, AuthService);
        MatchmakingService = OnlineMatchmakingService;

        UPDOnlineCollectionService* OnlineCollectionService = NewObject<UPDOnlineCollectionService>(this);
        OnlineCollectionService->Init(HttpRequestBuilder);
        CollectionService = OnlineCollectionService;

        UPDOnlineDeckListService* OnlineDeckListService = NewObject<UPDOnlineDeckListService>(this);
        OnlineDeckListService->Init(HttpRequestBuilder);
        DeckListService = OnlineDeckListService;

        UPDOnlineQuestService* OnlineQuestService = NewObject<UPDOnlineQuestService>(this);
        OnlineQuestService->Init(HttpRequestBuilder);
        QuestService = OnlineQuestService;
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

UPDCollectionService* UPDGameInstance::GetCollectionService() const
{
    return CollectionService;
}

UPDDeckListService* UPDGameInstance::GetDeckListService() const
{
    return DeckListService;
}

UPDMatchmakingService* UPDGameInstance::GetMatchmakingService() const
{
    return MatchmakingService;
}

UPDQuestService* UPDGameInstance::GetQuestService() const
{
    return QuestService;
}
