#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Data/PDCardAffiliation.h"
#include "Data/PDCardType.h"

#include "PDGameplayTagsComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDGameplayTagsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    EPDCardType GetCardType() const;

    UFUNCTION(BlueprintPure)
    EPDCardAffiliation GetCardAffiliation() const;

private:
    UPROPERTY(VisibleAnywhere)
    TArray<FString> InitialGameplayTags;
};
