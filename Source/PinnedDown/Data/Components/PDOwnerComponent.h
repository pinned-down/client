#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDOwnerComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOwnerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    int64 GetOwnerEntityId() const;

    void SetOwnerEntityId(int64 InOwnerEntityId);

private:
    UPROPERTY(VisibleAnywhere)
    int64 OwnerEntityId;
};
