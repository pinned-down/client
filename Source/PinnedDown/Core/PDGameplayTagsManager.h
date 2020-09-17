#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDGameplayTagsManager.generated.h"

class UPDEventManager;

UCLASS(BlueprintType, Blueprintable)
class PINNEDDOWN_API UPDGameplayTagsManager : public UObject
{
    GENERATED_BODY()

public:
    void Init(UPDEventManager* InEventManager);

    TArray<FString> GetGlobalGameplayTags() const;

    bool HasAllGlobalTags(TArray<FString> Tags) const;

private:
    UPROPERTY()
    UPDEventManager* EventManager;

    TArray<FString> GlobalGameplayTags;

    UFUNCTION()
    void OnGlobalGameplayTagsChanged(const UObject* EventData);
};
