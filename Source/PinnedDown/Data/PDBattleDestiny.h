#pragma once

#include "CoreMinimal.h"

#include "PDBattleDestiny.generated.h"

class APDCardActor;

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDBattleDestiny
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    APDCardActor* Target;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    APDCardActor* BattleDestinyCard;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 BattleDestiny;
};
