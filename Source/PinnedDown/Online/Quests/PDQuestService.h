#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineService.h"

#include "Online/PDOnlineRequest.h"
#include "Online/Quests/PDQuestsCreateRequest.h"
#include "Online/Quests/PDQuestsFinishRequest.h"

#include "PDQuestService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDQuestService : public UPDOnlineService
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
    virtual void CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);

	UFUNCTION(BlueprintCallable)
	virtual void FinishQuest(const FString& QuestDefinitionId, const FPDQuestsFinishSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError);
};
