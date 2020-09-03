#include "PDCardActorManager.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDCardActor.h"
#include "Core/PDDelegate.h"
#include "Core/PDPlayerController.h"
#include "Data/Components/PDAssignmentComponent.h"
#include "Data/Components/PDAttachmentComponent.h"
#include "Data/Components/PDOwnerComponent.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDCardPlayedEvent.h"
#include "Events/EventData/PDCurrentLocationChangedEvent.h"
#include "Events/EventData/PDPlayerHandChangedEvent.h"
#include "Events/EventData/PDStarshipAssignedEvent.h"
#include "Events/EventData/PDStarshipDamagedEvent.h"

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

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipAssigned, &UPDCardActorManager::OnStarshipAssigned);
    EventManager->AddListener(TEXT("PDStarshipAssignedEvent"), OnStarshipAssigned);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnStarshipDamaged, &UPDCardActorManager::OnStarshipDamaged);
    EventManager->AddListener(TEXT("PDStarshipDamagedEvent"), OnStarshipDamaged);
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

        // Set owner.
        UPDOwnerComponent* OwnerComponent = CardActor->FindComponentByClass<UPDOwnerComponent>();
        OwnerComponent->SetOwnerEntityId(CardPlayedEvent->OwnerEntityId);
    }
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

        // Store attachment.
        UPDAttachmentComponent* AttachmentComponent = CardActor->FindComponentByClass<UPDAttachmentComponent>();

        if (IsValid(AttachmentComponent))
        {
            AttachmentComponent->SetAttachedTo(AttachedTo);
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

    Cards.Add(EntityId, CardActor);
}
