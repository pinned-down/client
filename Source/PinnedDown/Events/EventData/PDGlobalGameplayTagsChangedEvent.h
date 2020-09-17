#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDGlobalGameplayTagsChangedEvent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDGlobalGameplayTagsChangedEvent : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<FString> GlobalGameplayTags;
};
