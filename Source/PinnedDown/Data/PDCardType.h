#pragma once

#include "CoreMinimal.h"

#include "PDCardType.generated.h"

UENUM(BlueprintType)
enum class EPDCardType : uint8
{
    CARDTYPE_Invalid,
    CARDTYPE_Damage,
    CARDTYPE_Effect,
    CARDTYPE_Location,
    CARDTYPE_Starship
};
