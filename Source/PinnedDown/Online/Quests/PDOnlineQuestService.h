#pragma once

#include "CoreMinimal.h"

#include "Online/Quests/PDQuestService.h"

#include "PDOnlineQuestService.generated.h"

class UPDOnlineHttpRequestBuilder;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDOnlineQuestService : public UPDQuestService
{
	GENERATED_BODY()

public:
	void Init(UPDOnlineHttpRequestBuilder* InHttpRequestBuilder);

	void CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
	
private:
	UPROPERTY()
	UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

	UFUNCTION()
    void OnCreateSuccess(const FPDQuestsCreateResponseData& Response);

	UFUNCTION()
    void OnCreateError(const FString& ErrorMessage);
};
