#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "JsonObjectConverter.h"
#include "HttpModule.h"

#include "PDOnlineLibrary.generated.h"

struct FPDOnlineError;

UCLASS()
class PINNEDDOWN_API UPDOnlineLibrary : public UObject
{
    GENERATED_BODY()

public:
    template<typename RequestDataType>
    static TSharedRef<IHttpRequest> CreateHttpRequest(const FString& Url, const RequestDataType& RequestData)
    {
        FString JsonString;
        FJsonObjectConverter::UStructToJsonObjectString(RequestData, JsonString);

        FHttpModule* Http = &FHttpModule::Get();

        TSharedRef<IHttpRequest> Request = Http->CreateRequest();
        Request->SetURL(TEXT("http://localhost:9000") + Url);
        Request->SetHeader(TEXT("User-Agent"), TEXT("PinnedDown/1.0"));
        Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
        Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

        //if (!Authorization.IsEmpty())
        //{
        //    Request->SetHeader(TEXT("Authorization"), Authorization);
        //}

        Request->SetVerb("POST");
        Request->SetContentAsString(JsonString);

        return Request;
    }

    static FString LocalizeError(const FPDOnlineError& InError);
};
