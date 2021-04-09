#pragma once

#include "CoreMinimal.h"

#include "Online/Quests/PDQuestService.h"

#include "PDMockQuestService.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDMockQuestService : public UPDQuestService
{
	GENERATED_BODY()

public:
	void CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
};
