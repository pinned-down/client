#pragma once

#include "CoreMinimal.h"

#include "PDCardAffiliation.generated.h"

UENUM(BlueprintType)
enum class EPDCardAffiliation : uint8
{
    AFFILIATION_Invalid,
    AFFILIATION_BlueWing,
    AFFILIATION_GreenWing,
    AFFILIATION_PurpleWing,
    AFFILIATION_DraTar
};
