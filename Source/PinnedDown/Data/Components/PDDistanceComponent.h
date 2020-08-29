#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDDistanceComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDDistanceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    int32 GetDistance() const;

private:
    UPROPERTY(VisibleAnywhere)
    int32 Distance;
};
