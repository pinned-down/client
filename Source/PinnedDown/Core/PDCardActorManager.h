#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Core/PDCardActor.h"

#include "PDCardActorManager.generated.h"

class APDCardActor;
class UPDEventManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardHoveredSignature, APDCardActor*, HoveredActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardUnhoveredSignature, APDCardActor*, UnhoveredActor);

UCLASS(BlueprintType, Blueprintable)
class PINNEDDOWN_API UPDCardActorManager : public UObject
{
    GENERATED_BODY()

public:
    UPDCardActorManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void Init(UPDEventManager* InEventManager);

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardHoveredSignature OnCardHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardUnhoveredSignature OnCardUnhovered;

private:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<APDCardActor> CardActorClass;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerHandStartLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerHandCardPadding;

    UPROPERTY()
    UPDEventManager* EventManager;

    UPROPERTY()
    TMap<int64, APDCardActor*> Cards;

    UPROPERTY()
    TArray<APDCardActor*> HandCards;

    UFUNCTION()
    void OnPlayerHandChanged(const UObject* EventData);

    UFUNCTION()
    void OnBeginCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOver(AActor* TouchedActor);
};
