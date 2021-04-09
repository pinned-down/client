#include "PDOnlineQuestService.h"

void UPDOnlineQuestService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder)
{
    HttpRequestBuilder = InHttpRequestBuilder;
}

void UPDOnlineQuestService::CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDQuestsCreateSuccessSignature, OnServiceSuccess, &UPDOnlineQuestService::OnCreateSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineQuestService::OnCreateError);

    TSharedPtr<FPDQuestsCreateRequest> Request = MakeShared<FPDQuestsCreateRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineQuestService::OnCreateSuccess(const FPDQuestsCreateResponseData& Response)
{
    OnPendingRequestSuccess<FPDQuestsCreateRequest, FPDQuestsCreateResponseData>(Response);
}

void UPDOnlineQuestService::OnCreateError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
