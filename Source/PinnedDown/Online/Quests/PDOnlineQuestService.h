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

	virtual void CreateQuests(const FPDQuestsCreateSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
	virtual void FinishQuest(const FString& QuestDefinitionId, const FPDQuestsFinishSuccessSignature& OnSuccess, const FPDOnlineErrorSignature& OnError) override;
	
private:
	UPROPERTY()
	UPDOnlineHttpRequestBuilder* HttpRequestBuilder;

	UFUNCTION()
    void OnCreateSuccess(const FPDQuestsCreateResponseData& Response);

	UFUNCTION()
    void OnCreateError(const FString& ErrorMessage);

	UFUNCTION()
	void OnFinishSuccess(const FPDQuestsFinishResponseData& Response);

	UFUNCTION()
	void OnFinishError(const FString& ErrorMessage);
};
