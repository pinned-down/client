#include "PDCollectionClaimRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDCollectionClaimRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpPostRequest(TEXT("/open-game-backend-collection/client/claimitemset"));

    Request->OnProcessRequestComplete().BindRaw(this, &FPDCollectionClaimRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDCollectionClaimRequest::ToString()
{
    return TEXT("FPDCollectionClaimRequest");
}

void FPDCollectionClaimRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDCollectionClaimResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Checked for items to claim - ItemSetId: %s"), *ResponseData.ItemSetId);

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
