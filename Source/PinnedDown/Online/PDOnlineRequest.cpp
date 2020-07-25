#include "PDOnlineRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "PDOnlineLibrary.h"

FPDOnlineRequest::FPDOnlineRequest()
{
}

FPDOnlineRequest::~FPDOnlineRequest()
{
}

void FPDOnlineRequest::Execute()
{
}

FString FPDOnlineRequest::ToString()
{
    return TEXT("FPDOnlineRequest");
}

FString FPDOnlineRequest::CheckForErrors(FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        return NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString();
    }

    if (!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        FJsonObjectConverter::JsonObjectStringToUStruct<FPDOnlineError>(Response->GetContentAsString(), &Error, 0, 0);
        return UPDOnlineLibrary::LocalizeError(Error);
    }

    return TEXT("");
}
