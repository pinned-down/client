#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Data/PDAbility.h"

#include "PDAbilitiesComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAbilitiesComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    TArray<FString> GetAbilityIds() const;

    UFUNCTION(BlueprintPure)
    TArray<FPDAbility> GetAbilities() const;

private:
    UPROPERTY(VisibleAnywhere)
    TArray<FString> Abilities;
};
