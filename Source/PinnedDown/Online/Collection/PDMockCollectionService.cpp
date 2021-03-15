#include "PDMockCollectionService.h"

void UPDMockCollectionService::Get(const FPDCollectionGetSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDCollectionGetResponseData Response;

    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("Defiance"), 4));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("EvasionManeuver"), 4));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("FireAtWill"), 4));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("RaiseTheStakes"), 4));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("TargetEliminated"), 4));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("TRBArdor"), 1));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("TRBFaith"), 1));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("TRBJustice"), 1));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("TRBTruth"), 1));
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("TRBUnity"), 1));
    
    OnSuccess.ExecuteIfBound(Response);
}
