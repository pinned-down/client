#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Online/Quests/PDQuestsFinishResponseData.h"

#include "PDQuestsFinishRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDQuestsFinishSuccessSignature, const FPDQuestsFinishResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDQuestsFinishRequest : public FPDOnlineRequest
{
	GENERATED_BODY()

public:
	FString QuestDefinitionId;
	FPDQuestsFinishResponseData ResponseData;

	FPDQuestsFinishSuccessSignature OnSuccess;
	FPDQuestsFinishSuccessSignature OnServiceSuccess;

	virtual void Execute() override;
	virtual FString ToString() override;

	private:
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
