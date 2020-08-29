#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDThreatComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDThreatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    int32 GetThreat() const;

private:
    UPROPERTY(VisibleAnywhere)
    int32 Threat;
};
