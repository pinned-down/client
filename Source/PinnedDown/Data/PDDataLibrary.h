#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Data/PDCardAffiliation.h"
#include "Data/PDDeckList.h"

#include "PDDataLibrary.generated.h"

UCLASS()
class PINNEDDOWN_API UPDDataLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    static EPDCardAffiliation GetDeckAffiliation(const FPDDeckList& DeckList);

    UFUNCTION(BlueprintPure)
    static int32 GetCardCount(const FPDDeckList& DeckList, const FName& CardId);

    UFUNCTION(BlueprintCallable)
    static void SetCardCount(UPARAM(ref) FPDDeckList& DeckList, const FName& CardId, int32 NewCount);
};
