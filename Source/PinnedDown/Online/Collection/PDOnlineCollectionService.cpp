#include "PDOnlineCollectionService.h"

void UPDOnlineCollectionService::Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder)
{
    HttpRequestBuilder = InHttpRequestBuilder;
}

void UPDOnlineCollectionService::Get(const FPDCollectionGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    PDCreateDynamicDelegate(FPDCollectionGetSuccessSignature, OnServiceSuccess, &UPDOnlineCollectionService::OnGetSuccess);
    PDCreateDynamicDelegate(FPDOnlineErrorSignature, OnServiceError, &UPDOnlineCollectionService::OnGetError);

    TSharedPtr<FPDCollectionGetRequest> Request = MakeShared<FPDCollectionGetRequest>();
    Request->HttpRequestBuilder = HttpRequestBuilder;

    AddRequest(Request, OnSuccess, OnServiceSuccess, OnError, OnServiceError);
}

void UPDOnlineCollectionService::OnGetSuccess(const FPDCollectionGetResponseData& Response)
{
    OnPendingRequestSuccess<FPDCollectionGetRequest, FPDCollectionGetResponseData>(Response);
}

void UPDOnlineCollectionService::OnGetError(const FString& ErrorMessage)
{
    OnPendingRequestError(ErrorMessage);
}
