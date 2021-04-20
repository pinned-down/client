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

void UPDOnlineQuestService::FinishQuest(const FString& QuestDefinitionId,
    const FPDQuestsFinishSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDQuestsFinishSuccessSignature, OnServiceSuccess, &UPDOnlineQuestService::OnFinishSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineQuestService::OnFinishError);

    TSharedPtr<FPDQuestsFinishRequest> Request = MakeShared<FPDQuestsFinishRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->QuestDefinitionId = QuestDefinitionId;
    
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

void UPDOnlineQuestService::OnFinishSuccess(const FPDQuestsFinishResponseData& Response)
{
    OnPendingRequestSuccess<FPDQuestsFinishRequest, FPDQuestsFinishResponseData>(Response);
}

void UPDOnlineQuestService::OnFinishError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
