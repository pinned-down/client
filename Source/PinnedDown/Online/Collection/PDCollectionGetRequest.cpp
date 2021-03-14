#include "PDCollectionGetRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDCollectionGetRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpRequest(TEXT("/pinneddown-collection/get"));

    Request->OnProcessRequestComplete().BindRaw(this, &FPDCollectionGetRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDCollectionGetRequest::ToString()
{
    return TEXT("FPDCollectionGetRequest");
}

void FPDCollectionGetRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDCollectionGetResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Collection Fetched - Num Different Cards: %i"), ResponseData.Collection.Num());

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
