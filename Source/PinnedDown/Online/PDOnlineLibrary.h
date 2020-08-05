#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "JsonObjectConverter.h"
#include "HttpModule.h"

#include "PDOnlineLibrary.generated.h"

struct FPDOnlineError;

UCLASS()
class PINNEDDOWN_API UPDOnlineLibrary : public UObject
{
    GENERATED_BODY()

public:
    static FString LocalizeError(const FPDOnlineError& InError);
};
