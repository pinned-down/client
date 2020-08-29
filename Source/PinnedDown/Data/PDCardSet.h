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

    TSharedPtr<FJsonObject> GetCardAttributes(const FName& CardId) const;

private:
    FString Hash;
    TMap<FName, TSharedPtr<FJsonObject>> Cards;
};
