#pragma once

#include "CoreMinimal.h"

#include "Online/PDOnlineRequest.h"

#include "Interfaces/IHttpRequest.h"

#include "Online/Quests/PDQuestsCreateResponseData.h"

#include "PDQuestsCreateRequest.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDQuestsCreateSuccessSignature, const FPDQuestsCreateResponseData&, Response);

USTRUCT()
struct PINNEDDOWN_API FPDQuestsCreateRequest : public FPDOnlineRequest
{
	GENERATED_BODY()

public:
	FPDQuestsCreateResponseData ResponseData;

	FPDQuestsCreateSuccessSignature OnSuccess;
	FPDQuestsCreateSuccessSignature OnServiceSuccess;

	virtual void Execute() override;
	virtual FString ToString() override;

private:
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
