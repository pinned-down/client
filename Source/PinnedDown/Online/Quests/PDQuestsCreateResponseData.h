#pragma once

#include "CoreMinimal.h"

#include "PDQuestsCreateResponseDataItem.h"

#include "PDQuestsCreateResponseData.generated.h"

USTRUCT(BlueprintType)
struct PINNEDDOWN_API FPDQuestsCreateResponseData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FPDQuestsCreateResponseDataItem> Quests;
};
