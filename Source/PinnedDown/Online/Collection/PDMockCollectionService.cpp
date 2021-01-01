#include "PDMockCollectionService.h"

void UPDMockCollectionService::Get(const FPDCollectionGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDCollectionGetResponseData Response;

    Response.Collection.Add(TEXT("Defiance"), 4);
    Response.Collection.Add(TEXT("EvasionManeuver"), 4);
    Response.Collection.Add(TEXT("FireAtWill"), 4);
    Response.Collection.Add(TEXT("RaiseTheStakes"), 4);
    Response.Collection.Add(TEXT("TargetEliminated"), 4);
    Response.Collection.Add(TEXT("TRBArdor"), 1);
    Response.Collection.Add(TEXT("TRBFaith"), 1);
    Response.Collection.Add(TEXT("TRBJustice"), 1);
    Response.Collection.Add(TEXT("TRBTruth"), 1);
    Response.Collection.Add(TEXT("TRBUnity"), 1);

    OnSuccess.ExecuteIfBound(Response);
}
