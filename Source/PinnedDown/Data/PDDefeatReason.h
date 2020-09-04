#pragma once

#include "CoreMinimal.h"

#include "PDDefeatReason.generated.h"

UENUM(BlueprintType)
enum class EPDDefeatReason : uint8
{
    DEFEAT_Invalid,
    DEFEAT_FlagshipDestroyed,
    DEFEAT_Card
};
