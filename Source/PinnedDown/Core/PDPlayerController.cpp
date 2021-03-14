#include "PDPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDCardActorManager.h"
#include "Core/PDDelegate.h"
#include "Core/PDGameInstance.h"
#include "Core/PDGameMode.h"
#include "Core/PDLog.h"
#include "Events/PDAction.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDAssignStarshipAction.h"
#include "Events/EventData/PDEndAssignmentPhaseAction.h"
#include "Events/EventData/PDEndMainPhaseAction.h"
#include "Events/EventData/PDErrorEvent.h"
#include "Events/EventData/PDPlayerEntityCreatedEvent.h"
#include "Events/EventData/PDPlayEffectAction.h"
#include "Events/EventData/PDPlayStarshipAction.h"
#include "Events/EventData/PDResolveFightAction.h"
#include "Events/EventData/PDTurnPhaseStartedEvent.h"
#include "Online/Auth/PDAuthService.h"
#include "UI/PDUIMode.h"
#include "UI/PDUIModeAssignmentPhase.h"
#include "UI/PDUIModeFightPhase.h"
#include "UI/PDUIModeMainPhase.h"

void APDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Show mouse cursor.
    bShowMouseCursor = true;

    // Register for events.
    APDGameMode* GameMode = Cast<APDGameMode>(UGameplayStatics::GetGameMode(this));

    if (!IsValid(GameMode))
    {
        return;
    }

    UPDEventManager* EventManager = GameMode->GetEventManager();

    if (!IsValid(EventManager))
    {
        return;
    }

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnPlayerEntityCreated, &APDPlayerController::OnPlayerEntityCreated);
    EventManager->AddListener(TEXT("PDPlayerEntityCreatedEvent"), OnPlayerEntityCreated);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnTurnPhaseStarted, &APDPlayerController::OnTurnPhaseStarted);
    EventManager->AddListener(TEXT("PDTurnPhaseStartedEvent"), OnTurnPhaseStarted);

    PDCreateDynamicDelegate(FPDEventListenerSignature, OnError, &APDPlayerController::OnError);
    EventManager->AddListener(TEXT("PDErrorEvent"), OnError);

    APDCardActorManager* CardActorManager = GameMode->GetCardActorManager();

    if (IsValid(CardActorManager))
    {
        CardActorManager->OnCardClicked.AddDynamic(this, &APDPlayerController::OnCardClicked);
    }

    GameplayTagsManager = GameMode->GetGameplayTagsManager();
}

bool APDPlayerController::IsLocalPlayer(int64 PlayerEntityId) const
{
    return PlayerEntityId == LocalPlayerEntityId;
}

void APDPlayerController::ServerEndMainPhase()
{
    UPDEndMainPhaseAction* Action = NewObject<UPDEndMainPhaseAction>(this);
    SendActionToServer(Action);
}

void APDPlayerController::ServerAssignStarship(int64 AssignedStarship, int64 AssignedTo)
{
    UPDAssignStarshipAction* Action = NewObject<UPDAssignStarshipAction>(this);
    Action->AssignedStarship = AssignedStarship;
    Action->AssignedTo = AssignedTo;
    SendActionToServer(Action);
}

void APDPlayerController::ServerEndAssignmentPhase()
{
    UPDEndAssignmentPhaseAction* Action = NewObject<UPDEndAssignmentPhaseAction>(this);
    SendActionToServer(Action);
}

void APDPlayerController::ServerResolveFight(int64 EntityId)
{
    UPDResolveFightAction* Action = NewObject<UPDResolveFightAction>(this);
    Action->EntityId = EntityId;
    SendActionToServer(Action);
}

void APDPlayerController::ServerPlayEffect(const FString& EffectCardId, int64 TargetEntityId)
{
    UPDPlayEffectAction* Action = NewObject<UPDPlayEffectAction>(this);
    Action->BlueprintId = EffectCardId;
    Action->TargetEntityId = TargetEntityId;
    SendActionToServer(Action);
}

void APDPlayerController::ServerPlayStarship(const FString& StarshipCardId)
{
    UPDPlayStarshipAction* Action = NewObject<UPDPlayStarshipAction>(this);
    Action->BlueprintId = StarshipCardId;
    SendActionToServer(Action);
}

void APDPlayerController::NotifyOnError(const FString& ErrorCode, const FText& ErrorMessage)
{
    ReceiveOnError(ErrorCode, ErrorMessage);
}

void APDPlayerController::NotifyOnHintChanged(const FText& Hint)
{
    ReceiveOnHintChanged(Hint);
}

void APDPlayerController::OnPlayerEntityCreated(const UObject* EventData)
{
    const UPDPlayerEntityCreatedEvent* PlayerEntityCreatedEvent = Cast<UPDPlayerEntityCreatedEvent>(EventData);

    // Compare player id.
    UPDGameInstance* GameInstance = GetGameInstance<UPDGameInstance>();

    if (!IsValid(GameInstance))
    {
        return;
    }

    UPDAuthService* AuthService = GameInstance->GetAuthService();

    if (!IsValid(AuthService))
    {
        return;
    }

    if (PlayerEntityCreatedEvent->PlayerId != AuthService->GetPlayerId())
    {
        return;
    }

    // Store local player entity id.
    LocalPlayerEntityId = PlayerEntityCreatedEvent->EntityId;

    UE_LOG(LogPD, Log, TEXT("Local player entity id is %i."), LocalPlayerEntityId);
}

void APDPlayerController::OnTurnPhaseStarted(const UObject* EventData)
{
    const UPDTurnPhaseStartedEvent* TurnPhasedStartedEvent = Cast<UPDTurnPhaseStartedEvent>(EventData);

    APDGameMode* GameMode = Cast<APDGameMode>(UGameplayStatics::GetGameMode(this));

    if (!IsValid(GameMode))
    {
        return;
    }

    switch (TurnPhasedStartedEvent->GetTurnPhase())
    {
    case EPDTurnPhase::TURNPHASE_Main:
        SetUIMode(NewObject<UPDUIModeMainPhase>(this));
        break;

    case EPDTurnPhase::TURNPHASE_Attack:
        SetUIMode(nullptr);
        break;

    case EPDTurnPhase::TURNPHASE_Assignment:
        SetUIMode(NewObject<UPDUIModeAssignmentPhase>(this));
        break;

    case EPDTurnPhase::TURNPHASE_Fight:
        SetUIMode(NewObject<UPDUIModeFightPhase>(this));
        break;

    case EPDTurnPhase::TURNPHASE_Jump:
        SetUIMode(nullptr);
        break;
    }
}

void APDPlayerController::OnError(const UObject* EventData)
{
    const UPDErrorEvent* ErrorEvent = Cast<UPDErrorEvent>(EventData);

    if (!SentActionIds.Remove(ErrorEvent->ActionId))
    {
        return;
    }

    FText ErrorMessage = FText::FromStringTable(ErrorLocalizationTableId, ErrorEvent->ErrorCode);

    NotifyOnError(ErrorEvent->ErrorCode, ErrorMessage);
}

void APDPlayerController::OnCardClicked(APDCardActor* ClickedActor)
{
    if (IsValid(UIMode))
    {
        UIMode->HandleCardClicked(ClickedActor);
    }
}

void APDPlayerController::OnHintChanged(const FText& Hint)
{
    NotifyOnHintChanged(Hint);
}

void APDPlayerController::SendActionToServer(UPDAction* Action)
{
    APDGameMode* GameMode = Cast<APDGameMode>(UGameplayStatics::GetGameMode(this));

    if (!IsValid(GameMode))
    {
        return;
    }

    // Assign action id.
    Action->ActionId = FGuid::NewGuid().ToString(EGuidFormats::Short);
    SentActionIds.Add(Action->ActionId);

    GameMode->SendActionToServer(Action);
}

void APDPlayerController::SetUIMode(UPDUIMode* NewUIMode)
{
    if (IsValid(UIMode))
    {
        UIMode->OnHintChanged.RemoveDynamic(this, &APDPlayerController::OnHintChanged);
    }

    OnHintChanged(FText::GetEmpty());

    UIMode = NewUIMode;
    
    if (IsValid(UIMode))
    {
        UIMode->OnHintChanged.AddDynamic(this, &APDPlayerController::OnHintChanged);

        UIMode->Init(this, GameplayTagsManager);
    }
}
