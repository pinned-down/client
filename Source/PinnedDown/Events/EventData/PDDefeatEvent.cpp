#include "PDDefeatEvent.h"

EPDDefeatReason UPDDefeatEvent::GetDefeatReason() const
{
    if (Reason == TEXT("FLAGSHIP_DESTROYED"))
    {
        return EPDDefeatReason::DEFEAT_FlagshipDestroyed;
    }
    else if (Reason == TEXT("CARD"))
    {
        return EPDDefeatReason::DEFEAT_Card;
    }

    return EPDDefeatReason::DEFEAT_Invalid;
}
