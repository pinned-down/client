#pragma once

#include "CoreMinimal.h"

#include "Online/Quests/PDQuestService.h"

#include "PDMockQuestService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMockQuestService : public UPDQuestService
{
	GENERATED_BODY()

public:
	virtual void CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
	virtual void FinishQuest(const FString& QuestDefinitionId, const FPDQuestsFinishSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
};
