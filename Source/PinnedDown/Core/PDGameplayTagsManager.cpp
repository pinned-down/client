#include "PDGameplayTagsManager.h"

#include "Core/PDDelegate.h"
#include "Events/PDEventManager.h"
#include "Events/EventData/PDGlobalGameplayTagsChangedEvent.h"

void UPDGameplayTagsManager::Init(UPDEventManager* InEventManager)
{
    EventManager = InEventManager;

    // Register for events.
    PDCreateDynamicDelegate(FPDEventListenerSignature, OnGlobalGameplayTagsChanged, &UPDGameplayTagsManager::OnGlobalGameplayTagsChanged);
    EventManager->AddListener(TEXT("PDGlobalGameplayTagsChangedEvent"), OnGlobalGameplayTagsChanged);
}

TArray<FString> UPDGameplayTagsManager::GetGlobalGameplayTags() const
{
    return GlobalGameplayTags;
}

bool UPDGameplayTagsManager::HasAllGlobalTags(TArray<FString> Tags) const
{
    for (const FString& Tag : Tags)
    {
        if (!GlobalGameplayTags.Contains(Tag))
        {
            return false;
        }
    }

    return true;
}

void UPDGameplayTagsManager::OnGlobalGameplayTagsChanged(const UObject* EventData)
{
    const UPDGlobalGameplayTagsChangedEvent* GlobalGameplayTagsChangedEvent = Cast<UPDGlobalGameplayTagsChangedEvent>(EventData);
    GlobalGameplayTags = GlobalGameplayTagsChangedEvent->GlobalGameplayTags;
}
