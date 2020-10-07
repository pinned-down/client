#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "PDAbilityEffectMetadata.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAbilityEffectMetadata : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText EffectText;
};
