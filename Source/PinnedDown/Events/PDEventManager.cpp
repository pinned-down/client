#include "PDEventManager.h"

#include "Core/PDLog.h"

void UPDEventManager::AddListener(const FString& EventType, const FPDEventListenerSignature& EventListener)
{
    FPDEventListenerList& Listeners = EventListeners.FindOrAdd(EventType);
    Listeners.Add(EventListener);
}

void UPDEventManager::RemoveListener(const FString& EventType, const FPDEventListenerSignature& EventListener)
{
    FPDEventListenerList& Listeners = EventListeners.FindOrAdd(EventType);
    Listeners.Remove(EventListener);
}

void UPDEventManager::RaiseEvent(const FString& EventType, const UObject* EventData)
{
    FPDEventListenerList ListenerList = EventListeners.FindRef(EventType);

    for (const FPDEventListenerSignature& Listener : ListenerList.GetListeners())
    {
        Listener.ExecuteIfBound(EventData);
    }
}
