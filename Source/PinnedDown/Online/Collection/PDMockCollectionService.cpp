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
    Response.Collection.Add(FPDCollectionGetResponseDataItem(TEXT("PremiereCardPack"), 2));
    
    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockCollectionService::Claim(const FPDCollectionClaimSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDCollectionClaimResponseData Response;
    OnSuccess.ExecuteIfBound(Response);
}

void UPDMockCollectionService::OpenCardPack(const FString& ItemDefinitionId, const FPDCollectionOpenCardPackSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError)
{
    FPDCollectionOpenCardPackResponseData Response;

    Response.AddedItems.Add(TEXT("Defiance"), 1);
    Response.AddedItems.Add(TEXT("EvasionManeuver"), 1);
    Response.AddedItems.Add(TEXT("FireAtWill"), 1);
    Response.AddedItems.Add(TEXT("RaiseTheStakes"), 1);
    Response.AddedItems.Add(TEXT("TargetEliminated"), 1);

    OnSuccess.ExecuteIfBound(Response);
}
