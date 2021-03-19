#include "PDCollectionOpenCardPackRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "Online/PDOnlineHttpRequestBuilder.h"
#include "Online/PDOnlineLog.h"

void FPDCollectionOpenCardPackRequest::Execute()
{
    FHttpRequestRef Request = HttpRequestBuilder->CreateHttpPostRequest(TEXT("/open-game-backend-collection/client/opencontainer/" + ItemDefinitionId));

    Request->OnProcessRequestComplete().BindRaw(this, &FPDCollectionOpenCardPackRequest::OnHttpResponse);

    if (!Request->ProcessRequest())
    {
        OnServiceError.ExecuteIfBound(NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString());
        return;
    }
}

FString FPDCollectionOpenCardPackRequest::ToString()
{
    return TEXT("FPDCollectionOpenCardPackRequest - ItemDefinitionId: " + ItemDefinitionId);
}

void FPDCollectionOpenCardPackRequest::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!CheckForErrors(Response, bWasSuccessful))
    {
        return;
    }

    FJsonObjectConverter::JsonObjectStringToUStruct<FPDCollectionOpenCardPackResponseData>(Response->GetContentAsString(), &ResponseData, 0, 0);

    UE_LOG(LogPDOnline, Log, TEXT("Opened card pack - Different Cards: %i"), ResponseData.AddedItems.Num());

    OnServiceSuccess.ExecuteIfBound(ResponseData);
}
