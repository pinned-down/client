#pragma once

#include "CoreMinimal.h"

#include "GameFramework/CheatManager.h"

#include "PDCheatManager.generated.h"

UCLASS()
class PINNEDDOWN_API UPDCheatManager : public UCheatManager
{
    GENERATED_BODY()

public:
    virtual void God() override;
};
