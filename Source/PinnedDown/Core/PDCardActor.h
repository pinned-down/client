#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "PDCardActor.generated.h"

class UPDDistanceComponent;
class UPDGameplayTagsComponent;
class UPDPowerComponent;
class UPDStructureComponent;
class UPDThreatComponent;
class UPDVisualizationComponent;

UCLASS(BlueprintType, Blueprintable)
class PINNEDDOWN_API APDCardActor : public AActor
{
    GENERATED_BODY()

public:
    APDCardActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UFUNCTION(BlueprintCallable)
    void Init(int64 InEntityId, const FName& InCardId);

    UFUNCTION(BlueprintImplementableEvent)
    void OnCardInitialized(int64 InEntityId, const FName& InCardId);

private:
    UPROPERTY(VisibleAnywhere)
    int64 EntityId;

    UPROPERTY(VisibleAnywhere)
    FName CardId;

    UPROPERTY(VisibleAnywhere)
    UPDDistanceComponent* DistanceComponent;

    UPROPERTY(VisibleAnywhere)
    UPDGameplayTagsComponent* GameplayTagsComponent;

    UPROPERTY(VisibleAnywhere)
    UPDPowerComponent* PowerComponent;

    UPROPERTY(VisibleAnywhere)
    UPDStructureComponent* StructureComponent;

    UPROPERTY(VisibleAnywhere)
    UPDThreatComponent* ThreatComponent;

    UPROPERTY(VisibleAnywhere)
    UPDVisualizationComponent* VisualizationComponent;
};
