#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Data/PDCardAffiliation.h"
#include "Data/PDCardType.h"

#include "PDCardSet.generated.h"

class FJsonObject;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDCardSet : public UObject
{
    GENERATED_BODY()

public:
    void LoadFromDisk();

    FString GetHash() const;

    UFUNCTION(BlueprintPure)
    int32 Num() const;

    TArray<FName> GetCardIds() const;

    UFUNCTION(BlueprintPure)
    TArray<FName> GetCardTags(const FName& CardId) const;

    UFUNCTION(BlueprintPure)
    EPDCardType GetCardType(const FName& CardId) const;

    UFUNCTION(BlueprintPure)
    int32 GetCardThreat(const FName& CardId) const;

    UFUNCTION(BlueprintPure)
    EPDCardAffiliation GetCardAffiliation(const FName& CardId) const;

    UFUNCTION(BlueprintPure)
    int32 GetCardPower(const FName& CardId) const;

    UFUNCTION(BlueprintPure)
    int32 GetCardDistance(const FName& CardId) const;

    UFUNCTION(BlueprintPure)
    int32 GetCardDamage(const FName& CardId) const;

    TSharedPtr<FJsonObject> GetCardAttributes(const FName& CardId) const;

private:
    FString Hash;
    TMap<FName, TSharedPtr<FJsonObject>> Cards;
};
