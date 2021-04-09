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
