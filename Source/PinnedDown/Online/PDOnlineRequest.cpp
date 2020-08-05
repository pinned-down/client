#include "PDOnlineRequest.h"

#include "Interfaces/IHttpResponse.h"

#include "PDOnlineLibrary.h"
#include "PDOnlineLog.h"

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

bool FPDOnlineRequest::CheckForErrors(FHttpResponsePtr Response, bool bWasSuccessful)
{
    FString ErrorMessage;

    if (!bWasSuccessful || !Response.IsValid())
    {
        ErrorMessage = NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString();
    }

    if (!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        FJsonObjectConverter::JsonObjectStringToUStruct<FPDOnlineError>(Response->GetContentAsString(), &Error, 0, 0);
        ErrorMessage = UPDOnlineLibrary::LocalizeError(Error);

        if (ErrorMessage.IsEmpty())
        {
            UE_LOG(LogPDOnline, Error, TEXT("%s"), *Response->GetContentAsString());

            ErrorMessage = NSLOCTEXT("PinnedDownUI", "Error.UnableToConnect", "Unable to connect to server.").ToString();
        }
    }

    if (!ErrorMessage.IsEmpty())
    {
        OnServiceError.ExecuteIfBound(ErrorMessage);
        return false;
    }

    return true;
}
