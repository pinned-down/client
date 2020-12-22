#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "JsonObjectConverter.h"
#include "HttpModule.h"

#include "PDOnlineHttpRequestBuilder.generated.h"

UCLASS()
class PINNEDDOWN_API UPDOnlineHttpRequestBuilder : public UObject
{
    GENERATED_BODY()

public:
    FString Authorization;

    TSharedRef<IHttpRequest> CreateHttpRequest(const FString& Url) const
    {
        FHttpModule* Http = &FHttpModule::Get();

        TSharedRef<IHttpRequest> Request = Http->CreateRequest();
        Request->SetVerb("GET");
        Request->SetURL(TEXT("http://localhost:9000") + Url);
        Request->SetHeader(TEXT("User-Agent"), TEXT("PinnedDown/1.0"));
        Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

        if (!Authorization.IsEmpty())
        {
            Request->SetHeader(TEXT("Authorization"), Authorization);
        }

        return Request;
    }

    template<typename RequestDataType>
    TSharedRef<IHttpRequest> CreateHttpRequest(const FString& Url, const RequestDataType& RequestData) const
    {
        FString JsonString;
        FJsonObjectConverter::UStructToJsonObjectString(RequestData, JsonString);

        TSharedRef<IHttpRequest> Request = CreateHttpRequest(Url);
        Request->SetVerb("POST");
        Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
        Request->SetContentAsString(JsonString);

        return Request;
    }
};
