#include "PDOnlineDeckListService.h"

void UPDOnlineDeckListService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder)
{
    HttpRequestBuilder = InHttpRequestBuilder;
}

void UPDOnlineDeckListService::Get(const FPDDeckListGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDDeckListGetSuccessSignature, OnServiceSuccess, &UPDOnlineDeckListService::OnGetSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineDeckListService::OnGetError);

    TSharedPtr<FPDDeckListGetRequest> Request = MakeShared<FPDDeckListGetRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineDeckListService::Put(int64 LoadoutId, const FPDDeckListPutRequestData& RequestData, const FPDDeckListPutSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDDeckListPutSuccessSignature, OnServiceSuccess, &UPDOnlineDeckListService::OnPutSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineDeckListService::OnPutError);

    TSharedPtr<FPDDeckListPutRequest> Request = MakeShared<FPDDeckListPutRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;
    Request->LoadoutId = LoadoutId;
    Request->RequestData = RequestData;

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineDeckListService::OnGetSuccess(const FPDDeckListGetResponseData& Response)
{
    OnPendingRequestSuccess<FPDDeckListGetRequest, FPDDeckListGetResponseData>(Response);
}

void UPDOnlineDeckListService::OnGetError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}

void UPDOnlineDeckListService::OnPutSuccess()
{
    OnPendingRequestSuccess<FPDDeckListPutRequest>();
}

void UPDOnlineDeckListService::OnPutError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
