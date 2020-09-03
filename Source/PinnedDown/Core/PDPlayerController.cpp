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
#include "Events/EventData/PDPlayerEntityCreatedEvent.h"
#include "Events/EventData/PDResolveFightAction.h"
#include "Events/EventData/PDTurnPhaseStartedEvent.h"
#include "Online/Auth/PDAuthService.h"
#include "UI/PDUIMode.h"
#include "UI/PDUIModeAssignmentPhase.h"
#include "UI/PDUIModeFightPhase.h"

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

    UPDCardActorManager* CardActorManager = GameMode->GetCardActorManager();

    if (IsValid(CardActorManager))
    {
        CardActorManager->OnCardClicked.AddDynamic(this, &APDPlayerController::OnCardClicked);
    }
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

    if (TurnPhasedStartedEvent->GetTurnPhase() == EPDTurnPhase::TURNPHASE_Assignment)
    {
        SetUIMode(NewObject<UPDUIModeAssignmentPhase>(this));
    }
    else if (TurnPhasedStartedEvent->GetTurnPhase() == EPDTurnPhase::TURNPHASE_Fight)
    {
        SetUIMode(NewObject<UPDUIModeFightPhase>(this));
    }
    else if (TurnPhasedStartedEvent->GetTurnPhase() == EPDTurnPhase::TURNPHASE_Jump)
    {
        SetUIMode(nullptr);
    }
}

void APDPlayerController::OnCardClicked(APDCardActor* ClickedActor)
{
    if (IsValid(UIMode))
    {
        UIMode->HandleCardClicked(ClickedActor);
    }
}

void APDPlayerController::SendActionToServer(UPDAction* Action)
{
    APDGameMode* GameMode = Cast<APDGameMode>(UGameplayStatics::GetGameMode(this));

    if (!IsValid(GameMode))
    {
        return;
    }

    GameMode->SendActionToServer(Action);
}

void APDPlayerController::SetUIMode(UPDUIMode* NewUIMode)
{
    UIMode = NewUIMode;

    if (IsValid(UIMode))
    {
        UIMode->Init(this);
    }
}
