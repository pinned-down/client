#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDAssignmentComponent.generated.h"

class APDCardActor;

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDAssignmentComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    APDCardActor* GetAssignedTo() const;

    void SetAssignedTo(APDCardActor* InAssignedTo);

private:
    UPROPERTY(VisibleAnywhere)
    APDCardActor* AssignedTo;
};
