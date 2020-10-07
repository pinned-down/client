#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDAbilityEffectActivatedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAbilityEffectActivatedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 EffectEntityId;

    UPROPERTY(BlueprintReadWrite)
    FString EffectBlueprintId;

    UPROPERTY(BlueprintReadWrite)
    FString AbilityBlueprintId;

    UPROPERTY(BlueprintReadWrite)
    int64 TargetEntityId;
};
