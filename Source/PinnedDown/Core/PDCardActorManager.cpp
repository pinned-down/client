#include "PDCardActorManager.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDCardActor.h"
#include "Core/PDDelegate.h"
#include "Core/PDPlayerController.h"
#include "Events/PDEventManager.h"
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
            CardActor->Init(0, FName(CardName));
            CardActor->OnBeginCursorOver.AddDynamic(this, &UPDCardActorManager::OnBeginCursorOver);
            CardActor->OnEndCursorOver.AddDynamic(this, &UPDCardActorManager::OnEndCursorOver);

            CardPadding += PlayerHandCardPadding;

            HandCards.Add(CardActor);
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
