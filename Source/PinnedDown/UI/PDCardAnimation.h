#pragma once

#include "CoreMinimal.h"

#include "PDCardAnimation.generated.h"

USTRUCT()
struct PINNEDDOWN_API FPDCardAnimation
{
    GENERATED_BODY()

public:
    UPROPERTY()
    float AnimationDelay;

    UPROPERTY()
    float AnimationDuration;

    UPROPERTY()
    float AnimationTimeElapsed;

    UPROPERTY()
    FVector StartLocation;

    UPROPERTY()
    FVector TargetLocation;

    UPROPERTY()
    bool bShowSmallVersion;
};
