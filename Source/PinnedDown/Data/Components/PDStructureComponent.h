#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDStructureComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDStructureComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    int32 GetBaseStructure() const;

    UFUNCTION(BlueprintPure)
    int32 GetStructureModifier() const;

private:
    UPROPERTY(VisibleAnywhere)
    int32 BaseStructure;

    UPROPERTY(VisibleAnywhere)
    int32 StructureModifier;
};
