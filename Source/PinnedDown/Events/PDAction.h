#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDAction.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAction : public UObject
{
    GENERATED_BODY()

public:
    FString Endpoint;
};
