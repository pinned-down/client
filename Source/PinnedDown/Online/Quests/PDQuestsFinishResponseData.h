#pragma once

#include "CoreMinimal.h"

#include "PDQuestsFinishResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDQuestsFinishResponseData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString RewardItemDefinitionId;

	UPROPERTY(BlueprintReadOnly)
	int32 RewardItemCount;
};
