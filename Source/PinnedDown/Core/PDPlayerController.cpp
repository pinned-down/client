#include "PDPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Core/PDDelegate.h"
#include "Core/PDGameInstance.h"
#include "Core/PDGameMode.h"
#include "Core/PDLog.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDPlayerEntityCreatedEvent.h"
#include "Online/Auth/PDAuthService.h"

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
}

bool APDPlayerController::IsLocalPlayer(int64 PlayerEntityId) const
{
    return PlayerEntityId == LocalPlayerEntityId;
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
