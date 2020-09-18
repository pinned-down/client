#include "PDCardActorManager.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDCardActor.h"
#include "Core/PDDelegate.h"
#include "Core/PDPlayerController.h"
#include "Data/PDCardType.h"
#include "Data/Components/PDAssignmentComponent.h"
#include "Data/Components/PDAttachmentComponent.h"
#include "Data/Components/PDGameplayTagsComponent.h"
#include "Data/Components/PDOwnerComponent.h"
#include "Data/Components/PDPowerComponent.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDCardPlayedEvent.h"
#include "Events/EventData/PDCardRemovedEvent.h"
#include "Events/EventData/PDPlayerDiscardPileChangedEvent.h"
#include "Events/EventData/PDPlayerDrawDeckSizeChangedEvent.h"
#include "Events/EventData/PDPlayerHandChangedEvent.h"
#include "Events/EventData/PDStarshipAssignedEvent.h"
#include "Events/EventData/PDStarshipDamagedEvent.h"
#include "Events/EventData/PDStarshipPowerChangedEvent.h"

UPDCardActorManager::UPDCardActorManager(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    CardActorClass = APDCardActor::StaticClass();
}

void UPDCardActorManager::Init()
{
    // Register for events.
    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerHandChanged, &UPDCardActorManager::OnPlayerHandChanged);
    EventManager->AddListener(TEXT("PDPlayerHandChangedEvent"), OnPlayerHandChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnCardPlayed, &UPDCardActorManager::OnCardPlayed);
    EventManager->AddListener(TEXT("PDCardPlayedEvent"), OnCardPlayed);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipAssigned, &UPDCardActorManager::OnStarshipAssigned);
    EventManager->AddListener(TEXT("PDStarshipAssignedEvent"), OnStarshipAssigned);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipDamaged, &UPDCardActorManager::OnStarshipDamaged);
    EventManager->AddListener(TEXT("PDStarshipDamagedEvent"), OnStarshipDamaged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnCardRemoved, &UPDCardActorManager::OnCardRemoved);
    EventManager->AddListener(TEXT("PDCardRemovedEvent"), OnCardRemoved);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipPowerChanged, &UPDCardActorManager::OnStarshipPowerChanged);
    EventManager->AddListener(TEXT("PDStarshipPowerChangedEvent"), OnStarshipPowerChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerDrawDeckSizeChanged, &UPDCardActorManager::OnPlayerDrawDeckSizeChanged);
    EventManager->AddListener(TEXT("PDPlayerDrawDeckSizeChangedEvent"), OnPlayerDrawDeckSizeChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerDiscardPileChanged, &UPDCardActorManager::OnPlayerDiscardPileChanged);
    EventManager->AddListener(TEXT("PDPlayerDiscardPileChangedEvent"), OnPlayerDiscardPileChanged);
}

APDCardActor* UPDCardActorManager::GetCardActor(int64 EntityId) const
{
    return Cards.FindRef(EntityId);
}

void UPDCardActorManager::OnPlayerDrawDeckSizeChanged(const UObject* EventData)
{
    const UPDPlayerDrawDeckSizeChangedEvent* PlayerDrawDeckSizeChangedEvent = Cast<UPDPlayerDrawDeckSizeChangedEvent>(EventData);

    APDPlayerController* PlayerController = Cast<APDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (!IsValid(PlayerController))
    {
        return;
    }

    if (!PlayerController->IsLocalPlayer(PlayerDrawDeckSizeChangedEvent->PlayerEntityId))
    {
        return;
    }

    if (PlayerDrawDeckSizeChangedEvent->DrawDeckSize > 0)
    {
        // Create top draw deck actor, if necessary.
        if (IsValid(TopDrawDeckCard))
        {
            return;
        }

        APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass);

        if (!IsValid(CardActor))
        {
            return;
        }

        CardActor->OnBeginCursorOver.AddDynamic(this, &UPDCardActorManager::OnBeginCursorOverDrawDeck);
        CardActor->OnEndCursorOver.AddDynamic(this, &UPDCardActorManager::OnEndCursorOverDrawDeck);

        CardActor->SetActorLocation(DrawDeckLocation);
        CardActor->SetActorRotation(DrawDeckRotation);

        TopDrawDeckCard = CardActor;
    }
    else
    {
        // Remove top draw deck card, if necessary.
        if (!IsValid(TopDrawDeckCard))
        {
            return;
        }

        TopDrawDeckCard->OnBeginCursorOver.RemoveDynamic(this, &UPDCardActorManager::OnBeginCursorOverDrawDeck);
        TopDrawDeckCard->OnEndCursorOver.RemoveDynamic(this, &UPDCardActorManager::OnEndCursorOverDrawDeck);

        TopDrawDeckCard->Destroy();

        TopDrawDeckCard = nullptr;
    }
}

void UPDCardActorManager::OnPlayerDiscardPileChanged(const UObject* EventData)
{
    const UPDPlayerDiscardPileChangedEvent* PlayerDiscardPileChangedEvent = Cast<UPDPlayerDiscardPileChangedEvent>(EventData);

    APDPlayerController* PlayerController = Cast<APDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (!IsValid(PlayerController))
    {
        return;
    }

    if (!PlayerController->IsLocalPlayer(PlayerDiscardPileChangedEvent->PlayerEntityId))
    {
        return;
    }

    // Clear old discard pile.
    for (APDCardActor* OldCard : DiscardPileCards)
    {
        OldCard->Destroy();
    }

    DiscardPileCards.Empty();

    // Create discard pile card actors.
    for (int32 Index = 0; Index < PlayerDiscardPileChangedEvent->Cards.Num(); ++Index)
    {
        const FString& CardName = PlayerDiscardPileChangedEvent->Cards[Index];

        APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass, DiscardPileLocation, FRotator::ZeroRotator);

        if (IsValid(CardActor))
        {
            CardActor->Init(0, FName(CardName));
            DiscardPileCards.Add(CardActor);

            // Show top card only.
            if (Index < PlayerDiscardPileChangedEvent->Cards.Num() - 1)
            {
                CardActor->SetActorHiddenInGame(true);
            }
            else
            {
                CardActor->OnBeginCursorOver.AddDynamic(this, &UPDCardActorManager::OnBeginCursorOverDiscardPile);
                CardActor->OnEndCursorOver.AddDynamic(this, &UPDCardActorManager::OnEndCursorOverDiscardPile);
                CardActor->OnClicked.AddDynamic(this, &UPDCardActorManager::OnClickedDiscardPile);
            }
        }
    }
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

void UPDCardActorManager::OnCardPlayed(const UObject* EventData)
{
    const UPDCardPlayedEvent* CardPlayedEvent = Cast<UPDCardPlayedEvent>(EventData);

    // Create card actor.
    APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass);

    if (!IsValid(CardActor))
    {
        return;
    }

    InitCardActor(CardActor, CardPlayedEvent->EntityId, CardPlayedEvent->BlueprintId);

    // Set owner.
    UPDOwnerComponent* OwnerComponent = CardActor->FindComponentByClass<UPDOwnerComponent>();
    OwnerComponent->SetOwnerEntityId(CardPlayedEvent->OwnerEntityId);

    // Check if location card.
    UPDGameplayTagsComponent* GameplayTagsComponent = CardActor->FindComponentByClass<UPDGameplayTagsComponent>();
    bool bIsLocationCard = IsValid(GameplayTagsComponent) && GameplayTagsComponent->GetCardType() == EPDCardType::CARDTYPE_Location;

    if (bIsLocationCard)
    {
        CardActor->SetActorLocation(LocationCardLocation);

        if (IsValid(CurrentLocationCard))
        {
            CurrentLocationCard->Destroy();
        }

        CurrentLocationCard = CardActor;
        return;
    }

    // Check if player card.
    APDPlayerController* PlayerController = Cast<APDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    bool bIsPlayerCard = IsValid(PlayerController) && PlayerController->IsLocalPlayer(CardPlayedEvent->OwnerEntityId);

    if (bIsPlayerCard)
    {
        CardActor->SetActorLocation(PlayerShipsStartLocation + LocalPlayerCards.Num() * PlayerShipsCardPadding);
        CardActor->SetShowSmallVersion(true);

        LocalPlayerCards.Add(CardActor);
        return;
    }

    // Must be enemy card.
    CardActor->SetActorLocation(EnemyShipsStartLocation + EnemyCards.Num() * EnemyShipsCardPadding);
    CardActor->SetShowSmallVersion(true);

    EnemyCards.Add(CardActor);
}

void UPDCardActorManager::OnStarshipAssigned(const UObject* EventData)
{
    const UPDStarshipAssignedEvent* StarshipAssignedEvent = Cast<UPDStarshipAssignedEvent>(EventData);

    APDCardActor* AssignedStarship = Cards.FindRef(StarshipAssignedEvent->AssignedStarship);
    APDCardActor* AssignedTo = Cards.FindRef(StarshipAssignedEvent->AssignedTo);

    if (!IsValid(AssignedStarship))
    {
        return;
    }

    // Store assignment.
    UPDAssignmentComponent* AssignmentComponent = AssignedStarship->FindComponentByClass<UPDAssignmentComponent>();

    if (IsValid(AssignmentComponent))
    {
        AssignmentComponent->SetAssignedTo(AssignedTo);
    }

    // Update actor location.
    if (IsValid(AssignedTo))
    {
        FVector NewLocation = AssignedTo->GetActorLocation() + AssignedCardOffset;
        AssignedStarship->SetActorLocation(NewLocation);
    }
    else
    {
        FVector NewLocation = PlayerShipsStartLocation + LocalPlayerCards.IndexOfByKey(AssignedStarship) * PlayerShipsCardPadding;
        AssignedStarship->SetActorLocation(NewLocation);
    }
}

void UPDCardActorManager::OnStarshipDamaged(const UObject* EventData)
{
    const UPDStarshipDamagedEvent* StarshipDamagedEvent = Cast<UPDStarshipDamagedEvent>(EventData);

    APDCardActor* AttachedTo = Cards.FindRef(StarshipDamagedEvent->StarshipEntityId);

    // Calculate actor location.
    int32 NumDamageCards = 1;

    for (APDCardActor* DamageCard : DamageCards)
    {
        UPDAttachmentComponent* OtherAttachmentComponent = DamageCard->FindComponentByClass<UPDAttachmentComponent>();

        if (IsValid(OtherAttachmentComponent) && OtherAttachmentComponent->GetAttachedTo() == AttachedTo)
        {
            ++NumDamageCards;
        }
    }

    FVector CardLocation = AttachedTo->GetActorLocation() + AttachedCardOffset * NumDamageCards;

    // Create card actor.
    APDCardActor* CardActor = GetWorld()->SpawnActor<APDCardActor>(CardActorClass, CardLocation, FRotator::ZeroRotator);

    if (IsValid(CardActor))
    {
        InitCardActor(CardActor, StarshipDamagedEvent->DamageEntityId, StarshipDamagedEvent->DamageBlueprintId);
        DamageCards.Add(CardActor);

        CardActor->AttachToActor(AttachedTo, FAttachmentTransformRules::KeepWorldTransform);
        CardActor->SetShowSmallVersion(true);

        // Store attachment.
        UPDAttachmentComponent* AttachmentComponent = CardActor->FindComponentByClass<UPDAttachmentComponent>();

        if (IsValid(AttachmentComponent))
        {
            AttachmentComponent->SetAttachedTo(AttachedTo);
        }
    }
}

void UPDCardActorManager::OnCardRemoved(const UObject* EventData)
{
    const UPDCardRemovedEvent* CardRemovedEvent = Cast<UPDCardRemovedEvent>(EventData);
    APDCardActor* RemovedCard = Cards.FindRef(CardRemovedEvent->EntityId);

    if (IsValid(RemovedCard))
    {
        Cards.Remove(RemovedCard->GetEntityId());

        HandCards.Remove(RemovedCard);
        LocalPlayerCards.Remove(RemovedCard);
        EnemyCards.Remove(RemovedCard);
        DamageCards.Remove(RemovedCard);

        RemovedCard->Destroy();
    }
}

void UPDCardActorManager::OnStarshipPowerChanged(const UObject* EventData)
{
    const UPDStarshipPowerChangedEvent* StarshipPowerChangedEvent = Cast<UPDStarshipPowerChangedEvent>(EventData);
    APDCardActor* Card = Cards.FindRef(StarshipPowerChangedEvent->EntityId);

    if (!IsValid(Card))
    {
        return;
    }

    UPDPowerComponent* PowerComponent = Card->FindComponentByClass<UPDPowerComponent>();

    if (!IsValid(PowerComponent))
    {
        return;
    }

    PowerComponent->SetPowerModifier(StarshipPowerChangedEvent->NewPowerModifier);
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

void UPDCardActorManager::OnBeginCursorOverDrawDeck(AActor* TouchedActor)
{
    OnDrawDeckHovered.Broadcast();
}

void UPDCardActorManager::OnEndCursorOverDrawDeck(AActor* TouchedActor)
{
    OnDrawDeckUnhovered.Broadcast();
}

void UPDCardActorManager::OnBeginCursorOverDiscardPile(AActor* TouchedActor)
{
    OnDiscardPileHovered.Broadcast();
}

void UPDCardActorManager::OnEndCursorOverDiscardPile(AActor* TouchedActor)
{
    OnDiscardPileUnhovered.Broadcast();
}

void UPDCardActorManager::OnClickedDiscardPile(AActor* TouchedActor, FKey ButtonPressed)
{
    OnDiscardPileClicked.Broadcast(DiscardPileCards);
}

void UPDCardActorManager::InitCardActor(APDCardActor* CardActor, int64 EntityId, const FString& CardId)
{
    CardActor->Init(EntityId, FName(CardId));
    CardActor->OnBeginCursorOver.AddDynamic(this, &UPDCardActorManager::OnBeginCursorOver);
    CardActor->OnEndCursorOver.AddDynamic(this, &UPDCardActorManager::OnEndCursorOver);
    CardActor->OnClicked.AddDynamic(this, &UPDCardActorManager::OnClicked);

    Cards.Add(EntityId, CardActor);
}
