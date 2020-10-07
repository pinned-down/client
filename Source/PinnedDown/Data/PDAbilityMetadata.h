#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "PDAbilityMetadata.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDAbilityMetadata : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSoftObjectPtr<UTexture2D> Image;
};
