#pragma once

#include "CoreMinimal.h"

#include "PDEventListener.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDEventListenerSignature, const UObject*, EventData);

USTRUCT()
struct PINNEDDOWN_API FPDEventListenerList
{
    GENERATED_BODY()

public:
    void Add(const FPDEventListenerSignature& Listener);
    void Remove(const FPDEventListenerSignature& Listener);
    TArray<FPDEventListenerSignature> GetListeners() const;

private:
    TArray<FPDEventListenerSignature> Listeners;
};
