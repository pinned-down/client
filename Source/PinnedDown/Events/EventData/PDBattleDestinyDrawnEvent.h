#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDBattleDestinyDrawnEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDBattleDestinyDrawnEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 TargetEntityId;

    UPROPERTY(BlueprintReadWrite)
    FString BattleDestinyCardBlueprintId;

    UPROPERTY(BlueprintReadWrite)
    int32 BattleDestiny;
};
