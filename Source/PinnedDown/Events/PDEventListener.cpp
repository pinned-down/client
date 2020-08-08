#include "PDEventListener.h"

void FPDEventListenerList::Add(const FPDEventListenerSignature& Listener)
{
    Listeners.Add(Listener);
}

void FPDEventListenerList::Remove(const FPDEventListenerSignature& Listener)
{
    Listeners.Remove(Listener);
}

TArray<FPDEventListenerSignature> FPDEventListenerList::GetListeners() const
{
    return Listeners;
}
