#include "PDThreatChangedEvent.h"

int32 UPDThreatChangedEvent::GetThreatChange() const
{
    return NewThreat - OldThreat;
}

EPDThreatChangeReason UPDThreatChangedEvent::GetThreatChangeReason() const
{
    if (Reason == TEXT("INITIAL_THREAT"))
    {
        return EPDThreatChangeReason::THREATCHANGE_InitialThreat;
    }
    else if (Reason == TEXT("ENEMY_CARD_PLAYED"))
    {
        return EPDThreatChangeReason::THREATCHANGE_EnemyCardPlayed;
    }
    else if (Reason == TEXT("ENEMY_CARD_DISCARDED"))
    {
        return EPDThreatChangeReason::THREATCHANGE_EnemyCardDiscarded;
    }
    else if (Reason == TEXT("UPKEEP"))
    {
        return EPDThreatChangeReason::THREATCHANGE_Upkeep;
    }
    else if (Reason == TEXT("PLAYER_CARD_PLAYED"))
    {
        return EPDThreatChangeReason::THREATCHANGE_PlayerCardPlayed;
    }
    else if (Reason == TEXT("TOTAL_DISTANCE"))
    {
        return EPDThreatChangeReason::THREATCHANGE_TotalDistance;
    }
    else if (Reason == TEXT("FLEET_SIZE"))
    {
        return EPDThreatChangeReason::THREATCHANGE_FleetSize;
    }

    return EPDThreatChangeReason::THREATCHANGE_Unknown;
}

FName UPDThreatChangedEvent::GetThreatChangeReasonCardId() const
{
    return FName(*ReasonEntityBlueprintId);
}
