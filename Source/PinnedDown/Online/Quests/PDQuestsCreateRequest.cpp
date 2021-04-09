#include "PDQuestsCreateRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDQuestsCreateRequest::Execute()
{
	FHttpRequestRef Request = HttpRequestBuilder->CreateHttpPostRequest(TEXT("/open-game-backend-quests/client/createquests"));

	Request->OnProcessRequestComplete().BindRaw(this, &FPDQuestsCreateRequest::OnHttpResponse);

	if (!Request->ProcessRequest())
	{
		OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
		return;
	}
}

FString FPDQuestsCreateRequest::ToString()
{
	return TEXT("FPDQuestsCreateRequest");
}

void FPDQuestsCreateRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!CheckForErrors(Response, bWasSuccessful))
	{
		return;
	}

	FJsonObjectConverter::JsonObjectStringToUStruct<FPDQuestsCreateResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

	UE_LOG(LogPDOnline, Log, TEXT("Quests created - Num: %i"), ResponseData.Quests.Num());

	OnServiceSuccess.ExecuteIfBound(ResponseData);
}
