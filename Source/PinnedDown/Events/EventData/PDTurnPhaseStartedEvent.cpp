#include "PDTurnPhaseStartedEvent.h"

EPDTurnPhase UPDTurnPhaseStartedEvent::GetTurnPhase() const
{
    if (TurnPhase == TEXT("MAIN"))
    {
        return EPDTurnPhase::TURNPHASE_Main;
    }
    else if (TurnPhase == TEXT("ATTACK"))
    {
        return EPDTurnPhase::TURNPHASE_Attack;
    }
    else if (TurnPhase == TEXT("ASSIGNMENT"))
    {
        return EPDTurnPhase::TURNPHASE_Assignment;
    }
    else if (TurnPhase == TEXT("FIGHT"))
    {
        return EPDTurnPhase::TURNPHASE_Fight;
    }
    else if (TurnPhase == TEXT("JUMP"))
    {
        return EPDTurnPhase::TURNPHASE_Jump;
    }

    return EPDTurnPhase::TURNPHASE_Invalid;
}
