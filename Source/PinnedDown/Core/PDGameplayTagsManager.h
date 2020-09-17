#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDGameplayTagsManager.generated.h"

class UPDEventManager;

UCLASS(BlueprintType, Blueprintable, meta=(Inject))
class PINNEDDOWN_API UPDGameplayTagsManager : public UObject
{
    GENERATED_BODY()

public:
    void Init();

    TArray<FString> GetGlobalGameplayTags() const;

    bool HasAllGlobalTags(TArray<FString> Tags) const;

private:
    UPROPERTY(meta=(Inject))
    UPDEventManager* EventManager;

    TArray<FString> GlobalGameplayTags;

    UFUNCTION()
    void OnGlobalGameplayTagsChanged(const UObject* EventData);
};
