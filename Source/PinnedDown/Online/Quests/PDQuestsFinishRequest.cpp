#include "PDQuestsFinishRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDQuestsFinishRequest::Execute()
{
	FHttpRequestRef Request = HttpRequestBuilder->CreateHttpPostRequest(TEXT("/open-game-backend-quests/client/finishquest/") + QuestDefinitionId);

	Request->OnProcessRequestComplete().BindRaw(this, &FPDQuestsFinishRequest::OnHttpResponse);

	if (!Request->ProcessRequest())
	{
		OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
		return;
	}
}

FString FPDQuestsFinishRequest::ToString()
{
	return TEXT("FPDQuestsFinishRequest");
}

void FPDQuestsFinishRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!CheckForErrors(Response, bWasSuccessful))
	{
		return;
	}

	FJsonObjectConverter::JsonObjectStringToUStruct<FPDQuestsFinishResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

	UE_LOG(LogPDOnline, Log, TEXT("Quest finished - %s, Reward: %i x %s"), *QuestDefinitionId, ResponseData.RewardItemCount, *ResponseData.RewardItemDefinitionId);

	ResponseData.QuestDefinitionId = QuestDefinitionId;
	OnServiceSuccess.ExecuteIfBound(ResponseData);
}
