#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "PDEventListener.h"

#include "PDEventManager.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDEventManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AddListener(const FString& EventType, const FPDEventListenerSignature& EventListener);

    UFUNCTION(BlueprintCallable)
    void RemoveListener(const FString& EventType, const FPDEventListenerSignature& EventListener);

    UFUNCTION(BlueprintCallable)
    void RaiseEvent(const FString& EventType,  const UObject* EventData);

private:
    UPROPERTY()
    TMap<FString, FPDEventListenerList> EventListeners;
};
