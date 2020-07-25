#include "PDOnlineLibrary.h"

#include "Online/PDOnlineError.h"
#include "Online/PDOnlineLog.h"

FString UPDOnlineLibrary::LocalizeError(const FPDOnlineError& InError)
{
    switch (InError.ErrorCode)
    {
    case 100:
        return NSLOCTEXT("PinnedDownUI", "Error.InvalidCredentials", "Invalid credentials.").ToString();

    case 101:
        return NSLOCTEXT("PinnedDownUI", "Error.InvalidAccessToken", "Invalid access token.").ToString();

    default:
        UE_LOG(LogPDOnline, Error, TEXT("Unlocalized error response - ErrorCode: %i, ErrorMessage: %s"), InError.ErrorCode,
            *InError.ErrorMessage);
        return InError.ErrorMessage;
    }
}
