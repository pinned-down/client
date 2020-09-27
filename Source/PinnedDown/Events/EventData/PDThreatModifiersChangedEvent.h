#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDThreatModifiersChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDThreatModifiersChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TMap<FString, int32> ThreatModifiers;
};
