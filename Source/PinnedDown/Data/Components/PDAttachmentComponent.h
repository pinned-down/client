#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDAttachmentComponent.generated.h"

class APDCardActor;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAttachmentComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    APDCardActor* GetAttachedTo() const;

    void SetAttachedTo(APDCardActor* InAttachedTo);

private:
    UPROPERTY(VisibleAnywhere)
    APDCardActor* AttachedTo;
};
