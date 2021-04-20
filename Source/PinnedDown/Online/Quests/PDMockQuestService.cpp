#include "PDMockQuestService.h"

void UPDMockQuestService::CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
	FPDQuestsCreateResponseDataItem Quest;
	Quest.QuestCategoryId = TEXT("DailyQuest");
	Quest.QuestDefinitionId = TEXT("ThreeWins");
	Quest.RequiredProgress = 3;
	Quest.CurrentProgress = 1;
	Quest.RewardItemDefinitionId = TEXT("Defiance");
	Quest.RewardItemCount = 1;
	Quest.bNewQuest = true;
	
	FPDQuestsCreateResponseData Response;
	Response.Quests.Add(Quest);
    
	OnSuccess.ExecuteIfBound(Response);
}

void UPDMockQuestService::FinishQuest(const FString& QuestDefinitionId,
	const FPDQuestsFinishSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
	FPDQuestsFinishResponseData Response;
	Response.RewardItemDefinitionId = TEXT("TestReward");
	Response.RewardItemCount = 100;

	OnSuccess.ExecuteIfBound(Response);
}
