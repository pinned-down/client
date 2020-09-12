#pragma once

#include "CoreMinimal.h"

#include "Data/PDAbilityTargetType.h"
#include "Data/PDTurnPhase.h"

#include "PDAbility.generated.h"

class APDCardActor;

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> RequiredTags;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> TargetRequiredTags;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> TargetBlockedTags;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString TargetType;

    EPDAbilityTargetType GetTargetType() const;
    EPDTurnPhase GetTurnPhase() const;
    bool IsValidTarget(const APDCardActor* Target) const;
};
