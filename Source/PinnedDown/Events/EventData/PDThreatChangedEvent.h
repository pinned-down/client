#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDThreatChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDThreatChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int32 NewThreat;
};
