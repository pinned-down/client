#include "PDCardActorManager.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDCardActor.h"
#include "Core/PDDelegate.h"
#include "Core/PDPlayerController.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDCardPlayedEvent.h"
#include "Events/EventData/PDCurrentLocationChangedEvent.h"
#include "Events/EventData/PDPlayerHandChangedEvent.h"

UPDCardActorManager::UPDCardActorManager(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    CardActorClass = APDCardActor::StaticClass();
}

void UPDCardActorManager::Init(UPDEventManager* InEventManager)
{
    EventManager = InEventManager;

    // Register for events.
    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerHandChanged, &UPDCardActorManager::OnPlayerHandChanged);
    EventManager->AddListener(TEXT("PDPlayerHandChangedEvent"), OnPlayerHandChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnCurrentLocationChanged, &UPDCardActorManager::OnCurrentLocationChanged);
    EventManager->AddListener(TEXT("PDCurrentLocationChangedEvent"), OnCurrentLocationChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnCardPlayed, &UPDCardActorManager::OnCardPlayed);
    EventManager->AddListener(TEXT("PDCardPlayedEvent"), OnCardPlayed);
}

void UPDCardActorManager::OnPlayerHandChanged(const UObject* EventData)
{
    const UPDPlayerHandChangedEvent* PlayerHandChangedEvent = Cast<UPDPlayerHandChangedEvent>(EventData);

    APDPlayerController* PlayerController = Cast<APDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (!IsValid(PlayerController))
    {
        return;
    }

    if (!PlayerController->IsLocalPlayer(PlayerHandChangedEvent->PlayerEntityId))
    {
        return;
    }

    // Clear old hand.
    for (APDCardActor* OldCard : HandCards)
    {
        OldCard->Destroy();
    }

    HandCards.Empty();

    // Create hand card actors.
    FVector CardPadding = FVector::ZeroVector;

    for (const FString& CardName : PlayerHandChangedEvent->Cards)
    {
        APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass, PlayerHandStartLocation + CardPadding, FRotator::ZeroRotator);

        if (IsValid(CardActor))
        {
            InitCardActor(CardActor, 0, CardName);

            CardPadding += PlayerHandCardPadding;

            HandCards.Add(CardActor);
        }
    }
}

void UPDCardActorManager::OnCurrentLocationChanged(const UObject* EventData)
{
    const UPDCurrentLocationChangedEvent* CurrentLocationChangedEvent = Cast<UPDCurrentLocationChangedEvent>(EventData);

    // Remove old location
    if (IsValid(CurrentLocationCard))
    {
        CurrentLocationCard->Destroy();
    }

    // Create location card actor.
    APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass, LocationCardLocation, FRotator::ZeroRotator);

    if (IsValid(CardActor))
    {
        InitCardActor(CardActor, 0, CurrentLocationChangedEvent->BlueprintId);
        CurrentLocationCard = CardActor;
    }
}

void UPDCardActorManager::OnCardPlayed(const UObject* EventData)
{
    const UPDCardPlayedEvent* CardPlayedEvent = Cast<UPDCardPlayedEvent>(EventData);

    APDPlayerController* PlayerController = Cast<APDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    bool bIsPlayerCard = IsValid(PlayerController) && PlayerController->IsLocalPlayer(CardPlayedEvent->OwnerEntityId);

    // Calculate location.
    FVector CardLocation;

    if (bIsPlayerCard)
    {
        CardLocation = PlayerShipsStartLocation + LocalPlayerCards.Num() * PlayerShipsCardPadding;
    }
    else
    {
        CardLocation = EnemyShipsStartLocation + EnemyCards.Num() * EnemyShipsCardPadding;
    }

    // Create card actor.
    APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass, CardLocation, FRotator::ZeroRotator);

    if (IsValid(CardActor))
    {
        InitCardActor(CardActor, CardPlayedEvent->EntityId, CardPlayedEvent->BlueprintId);

        if (bIsPlayerCard)
        {
            LocalPlayerCards.Add(CardActor);
        }
        else
        {
            EnemyCards.Add(CardActor);
        }
    }
}

void UPDCardActorManager::OnBeginCursorOver(AActor* TouchedActor)
{
    OnCardHovered.Broadcast(Cast<APDCardActor>(TouchedActor));
}

void UPDCardActorManager::OnEndCursorOver(AActor* TouchedActor)
{
    OnCardUnhovered.Broadcast(Cast<APDCardActor>(TouchedActor));
}

void UPDCardActorManager::OnClicked(AActor* TouchedActor, FKey ButtonPressed)
{
    OnCardClicked.Broadcast(Cast<APDCardActor>(TouchedActor));
}

void UPDCardActorManager::InitCardActor(APDCardActor* CardActor, int64 EntityId, const FString& CardId)
{
    CardActor->Init(EntityId, FName(CardId));
    CardActor->OnBeginCursorOver.AddDynamic(this, &UPDCardActorManager::OnBeginCursorOver);
    CardActor->OnEndCursorOver.AddDynamic(this, &UPDCardActorManager::OnEndCursorOver);
    CardActor->OnClicked.AddDynamic(this, &UPDCardActorManager::OnClicked);
}
