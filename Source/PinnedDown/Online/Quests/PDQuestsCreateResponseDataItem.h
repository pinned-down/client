#pragma once

#include "CoreMinimal.h"

#include "PDQuestsCreateResponseDataItem.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDQuestsCreateResponseDataItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int64 Id;

	UPROPERTY(BlueprintReadOnly)
	FString QuestCategoryId;

	UPROPERTY(BlueprintReadOnly)
	FString QuestDefinitionId;
	
	UPROPERTY(BlueprintReadOnly)
	int32 RequiredProgress;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentProgress;
	
	UPROPERTY(BlueprintReadOnly)
	FString RewardItemDefinitionId;
	
	UPROPERTY(BlueprintReadOnly)
	int32 RewardItemCount;

	UPROPERTY(BlueprintReadOnly)
	FString GeneratedAt;
	
	UPROPERTY(BlueprintReadOnly)
	bool bNewQuest;
};
