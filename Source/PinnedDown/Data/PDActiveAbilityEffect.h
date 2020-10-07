#pragma once

#include "CoreMinimal.h"

#include "PDActiveAbilityEffect.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDActiveAbilityEffect
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int64 EffectEntityId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName EffectId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName AbilityId;
};
