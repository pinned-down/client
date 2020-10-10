#include "PDCardActorManager.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDCardActor.h"
#include "Core/PDDelegate.h"
#include "Core/PDPlayerController.h"
#include "Data/PDActiveAbilityEffect.h"
#include "Data/PDCardType.h"
#include "Data/Components/PDAbilityEffectsComponent.h"
#include "Data/Components/PDAssignmentComponent.h"
#include "Data/Components/PDAttachmentComponent.h"
#include "Data/Components/PDGameplayTagsComponent.h"
#include "Data/Components/PDOwnerComponent.h"
#include "Data/Components/PDPowerComponent.h"
#include "Data/Components/PDThreatComponent.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDAbilityEffectActivatedEvent.h"
#include "Events/EventData/PDAbilityEffectDeactivatedEvent.h"
#include "Events/EventData/PDCardPlayedEvent.h"
#include "Events/EventData/PDCardRemovedEvent.h"
#include "Events/EventData/PDPlayerDiscardPileChangedEvent.h"
#include "Events/EventData/PDPlayerDrawDeckSizeChangedEvent.h"
#include "Events/EventData/PDPlayerHandChangedEvent.h"
#include "Events/EventData/PDStarshipAssignedEvent.h"
#include "Events/EventData/PDStarshipDamagedEvent.h"
#include "Events/EventData/PDStarshipPowerChangedEvent.h"
#include "Events/EventData/PDThreatModifiersChangedEvent.h"
#include "UI/PDCardAnimation.h"

APDCardActorManager::APDCardActorManager(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    CardActorClass = APDCardActor::StaticClass();
}

void APDCardActorManager::Init()
{
    // Register for events.
    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerHandChanged, &APDCardActorManager::OnPlayerHandChanged);
    EventManager->AddListener(TEXT("PDPlayerHandChangedEvent"), OnPlayerHandChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnCardPlayed, &APDCardActorManager::OnCardPlayed);
    EventManager->AddListener(TEXT("PDCardPlayedEvent"), OnCardPlayed);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipAssigned, &APDCardActorManager::OnStarshipAssigned);
    EventManager->AddListener(TEXT("PDStarshipAssignedEvent"), OnStarshipAssigned);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipDamaged, &APDCardActorManager::OnStarshipDamaged);
    EventManager->AddListener(TEXT("PDStarshipDamagedEvent"), OnStarshipDamaged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnCardRemoved, &APDCardActorManager::OnCardRemoved);
    EventManager->AddListener(TEXT("PDCardRemovedEvent"), OnCardRemoved);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipPowerChanged, &APDCardActorManager::OnStarshipPowerChanged);
    EventManager->AddListener(TEXT("PDStarshipPowerChangedEvent"), OnStarshipPowerChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerDrawDeckSizeChanged, &APDCardActorManager::OnPlayerDrawDeckSizeChanged);
    EventManager->AddListener(TEXT("PDPlayerDrawDeckSizeChangedEvent"), OnPlayerDrawDeckSizeChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerDiscardPileChanged, &APDCardActorManager::OnPlayerDiscardPileChanged);
    EventManager->AddListener(TEXT("PDPlayerDiscardPileChangedEvent"), OnPlayerDiscardPileChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, ThreatModifiersChanged, &APDCardActorManager::NotifyOnThreatModifiersChanged);
    EventManager->AddListener(TEXT("PDThreatModifiersChangedEvent"), ThreatModifiersChanged);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnAbilityEffectActivated, &APDCardActorManager::OnAbilityEffectActivated);
    EventManager->AddListener(TEXT("PDAbilityEffectActivatedEvent"), OnAbilityEffectActivated);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnAbilityEffectDeactivated, &APDCardActorManager::OnAbilityEffectDeactivated);
    EventManager->AddListener(TEXT("PDAbilityEffectDeactivatedEvent"), OnAbilityEffectDeactivated);
}

void APDCardActorManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (NewCards.Num() <= 0)
    {
        return;
    }

    // Update card animations.
    APDCardActor* NewCard = NewCards[0];
    FPDCardAnimation CardAnimation = NewCard->GetCardAnimation();

    NewCard->SetActorHiddenInGame(false);

    if (CardAnimation.AnimationDelay > 0.0f)
    {
        CardAnimation.AnimationDelay -= DeltaSeconds;

        NewCard->SetCardAnimation(CardAnimation);
    }
    else
    {
        CardAnimation.AnimationTimeElapsed += DeltaSeconds;
        float Alpha = FMath::Clamp(CardAnimation.AnimationTimeElapsed / CardAnimation.AnimationDuration, 0.0f, 1.0f);
        FVector NewLocation = FMath::InterpEaseInOut(CardAnimation.StartLocation,
            CardAnimation.TargetLocation, Alpha, 2.0f);
        NewCard->SetActorLocation(NewLocation);
        NewCard->SetShowSmallVersion(CardAnimation.bShowSmallVersion);

        if (CardAnimation.AnimationTimeElapsed >= CardAnimation.AnimationDuration)
        {
            NewCard->SetActorEnableCollision(true);
            NewCards.RemoveAt(0);
        }
        else
        {
            NewCard->SetCardAnimation(CardAnimation);
        }
    }
}

APDCardActor* APDCardActorManager::GetCardActor(int64 EntityId) const
{
    return Cards.FindRef(EntityId);
}

int32 APDCardActorManager::GetCardThreat(APDCardActor* CardActor) const
{
    UPDThreatComponent* ThreatComponent = CardActor->FindComponentByClass<UPDThreatComponent>();
    int32 CardThreat = IsValid(ThreatComponent) ? ThreatComponent->GetThreat() : 0;
    int32 ThreatModifier = ThreatModifiers.FindRef(CardActor->GetCardId().ToString());

    return CardThreat + ThreatModifier;
}

void APDCardActorManager::OnPlayerDrawDeckSizeChanged(const UObject* EventData)
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

        CardActor->OnBeginCursorOver.AddDynamic(this, &APDCardActorManager::OnBeginCursorOverDrawDeck);
        CardActor->OnEndCursorOver.AddDynamic(this, &APDCardActorManager::OnEndCursorOverDrawDeck);

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

        TopDrawDeckCard->OnBeginCursorOver.RemoveDynamic(this, &APDCardActorManager::OnBeginCursorOverDrawDeck);
        TopDrawDeckCard->OnEndCursorOver.RemoveDynamic(this, &APDCardActorManager::OnEndCursorOverDrawDeck);

        TopDrawDeckCard->Destroy();

        TopDrawDeckCard = nullptr;
    }
}

void APDCardActorManager::OnPlayerDiscardPileChanged(const UObject* EventData)
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
                CardActor->OnBeginCursorOver.AddDynamic(this, &APDCardActorManager::OnBeginCursorOverDiscardPile);
                CardActor->OnEndCursorOver.AddDynamic(this, &APDCardActorManager::OnEndCursorOverDiscardPile);
                CardActor->OnClicked.AddDynamic(this, &APDCardActorManager::OnClickedDiscardPile);
            }
        }
    }
}

void APDCardActorManager::OnPlayerHandChanged(const UObject* EventData)
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

void APDCardActorManager::OnCardPlayed(const UObject* EventData)
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
        FPDCardAnimation CardAnimation;
        CardAnimation.TargetLocation = LocationCardLocation + LocationCards.Num() * LocationCardPadding;
        CardAnimation.bShowSmallVersion = false;

        QueueCardAnimation(CardActor, CardAnimation);

        LocationCards.Add(CardActor);

        CardActor->OnBeginCursorOver.AddDynamic(this, &APDCardActorManager::OnBeginCursorOverLocationCard);
        CardActor->OnEndCursorOver.AddDynamic(this, &APDCardActorManager::OnEndCursorOverLocationCard);
        CardActor->OnClicked.AddDynamic(this, &APDCardActorManager::OnClickedLocationCard);

        return;
    }

    // Check if player card.
    APDPlayerController* PlayerController = Cast<APDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    bool bIsPlayerCard = IsValid(PlayerController) && PlayerController->IsLocalPlayer(CardPlayedEvent->OwnerEntityId);

    if (bIsPlayerCard)
    {
        FPDCardAnimation CardAnimation;
        CardAnimation.TargetLocation = PlayerShipsStartLocation + LocalPlayerCards.Num() * PlayerShipsCardPadding;
        CardAnimation.bShowSmallVersion = true;

        QueueCardAnimation(CardActor, CardAnimation);

        LocalPlayerCards.Add(CardActor);
        return;
    }

    // Must be enemy card.
    FPDCardAnimation CardAnimation;
    CardAnimation.TargetLocation = EnemyShipsStartLocation + EnemyCards.Num() * EnemyShipsCardPadding;
    CardAnimation.bShowSmallVersion = true;

    QueueCardAnimation(CardActor, CardAnimation);

    EnemyCards.Add(CardActor);
}

void APDCardActorManager::OnStarshipAssigned(const UObject* EventData)
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

void APDCardActorManager::OnStarshipDamaged(const UObject* EventData)
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

void APDCardActorManager::OnCardRemoved(const UObject* EventData)
{
    const UPDCardRemovedEvent* CardRemovedEvent = Cast<UPDCardRemovedEvent>(EventData);
    APDCardActor* RemovedCard = Cards.FindRef(CardRemovedEvent->EntityId);

    if (IsValid(RemovedCard) && !LocationCards.Contains(RemovedCard))
    {
        Cards.Remove(RemovedCard->GetEntityId());

        HandCards.Remove(RemovedCard);
        LocalPlayerCards.Remove(RemovedCard);
        EnemyCards.Remove(RemovedCard);
        DamageCards.Remove(RemovedCard);
        NewCards.Remove(RemovedCard);

        RemovedCard->Destroy();
    }
}

void APDCardActorManager::OnStarshipPowerChanged(const UObject* EventData)
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

void APDCardActorManager::NotifyOnThreatModifiersChanged(const UObject* EventData)
{
    const UPDThreatModifiersChangedEvent* ThreatModifiersChangedEvent = Cast<UPDThreatModifiersChangedEvent>(EventData);
    ThreatModifiers = ThreatModifiersChangedEvent->ThreatModifiers;

    OnThreatModifiersChanged.Broadcast();
}

void APDCardActorManager::OnAbilityEffectActivated(const UObject* EventData)
{
    const UPDAbilityEffectActivatedEvent* AbilityEffectActivatedEvent = Cast<UPDAbilityEffectActivatedEvent>(EventData);
    APDCardActor* EffectTarget = GetCardActor(AbilityEffectActivatedEvent->TargetEntityId);

    if (!IsValid(EffectTarget))
    {
        return;
    }

    UPDAbilityEffectsComponent* AbilityEffectsComponent = EffectTarget->FindComponentByClass<UPDAbilityEffectsComponent>();

    if (!IsValid(AbilityEffectsComponent))
    {
        return;
    }

    FPDActiveAbilityEffect NewEffect;
    NewEffect.EffectEntityId = AbilityEffectActivatedEvent->EffectEntityId;
    NewEffect.EffectId = FName(*AbilityEffectActivatedEvent->EffectBlueprintId);
    NewEffect.AbilityId = FName(*AbilityEffectActivatedEvent->AbilityBlueprintId);

    AbilityEffectsComponent->AddActiveEffect(NewEffect.EffectEntityId, NewEffect);

    // Notify listeners.
    OnActiveAbilityEffectsChanged.Broadcast(EffectTarget);
}

void APDCardActorManager::OnAbilityEffectDeactivated(const UObject* EventData)
{
    const UPDAbilityEffectDeactivatedEvent* AbilityEffectDeactivatedEvent = Cast<UPDAbilityEffectDeactivatedEvent>(EventData);
    APDCardActor* EffectTarget = GetCardActor(AbilityEffectDeactivatedEvent->TargetEntityId);

    if (!IsValid(EffectTarget))
    {
        return;
    }

    UPDAbilityEffectsComponent* AbilityEffectsComponent = EffectTarget->FindComponentByClass<UPDAbilityEffectsComponent>();

    if (!IsValid(AbilityEffectsComponent))
    {
        return;
    }

    AbilityEffectsComponent->RemoveActiveEffect(AbilityEffectDeactivatedEvent->EffectEntityId);

    // Notify listeners.
    OnActiveAbilityEffectsChanged.Broadcast(EffectTarget);
}

void APDCardActorManager::OnBeginCursorOver(AActor* TouchedActor)
{
    OnCardHovered.Broadcast(Cast<APDCardActor>(TouchedActor));
}

void APDCardActorManager::OnEndCursorOver(AActor* TouchedActor)
{
    OnCardUnhovered.Broadcast(Cast<APDCardActor>(TouchedActor));
}

void APDCardActorManager::OnClicked(AActor* TouchedActor, FKey ButtonPressed)
{
    OnCardClicked.Broadcast(Cast<APDCardActor>(TouchedActor));
}

void APDCardActorManager::OnBeginCursorOverDrawDeck(AActor* TouchedActor)
{
    OnDrawDeckHovered.Broadcast();
}

void APDCardActorManager::OnEndCursorOverDrawDeck(AActor* TouchedActor)
{
    OnDrawDeckUnhovered.Broadcast();
}

void APDCardActorManager::OnBeginCursorOverDiscardPile(AActor* TouchedActor)
{
    OnDiscardPileHovered.Broadcast();
}

void APDCardActorManager::OnEndCursorOverDiscardPile(AActor* TouchedActor)
{
    OnDiscardPileUnhovered.Broadcast();
}

void APDCardActorManager::OnClickedDiscardPile(AActor* TouchedActor, FKey ButtonPressed)
{
    OnDiscardPileClicked.Broadcast(DiscardPileCards);
}

void APDCardActorManager::OnBeginCursorOverLocationCard(AActor* TouchedActor)
{
    OnLocationCardHovered.Broadcast();
}

void APDCardActorManager::OnEndCursorOverLocationCard(AActor* TouchedActor)
{
    OnLocationCardUnhovered.Broadcast();
}

void APDCardActorManager::OnClickedLocationCard(AActor* TouchedActor, FKey ButtonPressed)
{
    OnLocationCardClicked.Broadcast(LocationCards);
}

void APDCardActorManager::InitCardActor(APDCardActor* CardActor, int64 EntityId, const FString& CardId)
{
    CardActor->Init(EntityId, FName(CardId));
    CardActor->OnBeginCursorOver.AddDynamic(this, &APDCardActorManager::OnBeginCursorOver);
    CardActor->OnEndCursorOver.AddDynamic(this, &APDCardActorManager::OnEndCursorOver);
    CardActor->OnClicked.AddDynamic(this, &APDCardActorManager::OnClicked);

    Cards.Add(EntityId, CardActor);
}

void APDCardActorManager::QueueCardAnimation(APDCardActor* CardActor, FPDCardAnimation CardAnimation)
{
    CardActor->SetActorLocation(PlayedCardLocation);

    CardAnimation.AnimationDelay = 2.0f;
    CardAnimation.AnimationDuration = 0.5f;
    CardAnimation.AnimationTimeElapsed = 0.0f;
    CardAnimation.StartLocation = CardActor->GetActorLocation();

    CardActor->SetCardAnimation(CardAnimation);
    NewCards.Add(CardActor);

    CardActor->SetActorHiddenInGame(true);
    CardActor->SetActorEnableCollision(false);
}
