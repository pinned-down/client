#pragma once

#include "CoreMinimal.h"

#include "PDTurnPhase.generated.h"

UENUM(BlueprintType)
enum class EPDTurnPhase : uint8
{
    TURNPHASE_Invalid,
    TURNPHASE_Main,
    TURNPHASE_Attack,
    TURNPHASE_Assignment,
    TURNPHASE_Fight,
    TURNPHASE_Jump
};
