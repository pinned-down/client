#pragma once

#include "CoreMinimal.h"

#include "PDAbilityTargetType.generated.h"

UENUM(BlueprintType)
enum class EPDAbilityTargetType : uint8
{
    TARGETTYPE_Passive,
    TARGETTYPE_Starship
};
