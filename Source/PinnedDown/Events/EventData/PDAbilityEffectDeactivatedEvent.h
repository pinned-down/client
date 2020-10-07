#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDAbilityEffectDeactivatedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAbilityEffectDeactivatedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int64 EffectEntityId;

    UPROPERTY(BlueprintReadWrite)
    int64 TargetEntityId;
};
