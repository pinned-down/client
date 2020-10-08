#pragma once

#include "CoreMinimal.h"

#include "PDThreatChangeReason.generated.h"

UENUM(BlueprintType)
enum class EPDThreatChangeReason : uint8
{
    THREATCHANGE_Unknown,
    THREATCHANGE_InitialThreat,
    THREATCHANGE_EnemyCardPlayed,
    THREATCHANGE_EnemyCardDiscarded,
    THREATCHANGE_Upkeep,
    THREATCHANGE_PlayerCardPlayed,
    THREATCHANGE_TotalDistance,
    THREATCHANGE_FleetSize,
};
