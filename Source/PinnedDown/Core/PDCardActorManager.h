#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Core/PDCardActor.h"

#include "PDCardActorManager.generated.h"

class APDCardActor;
class UPDEventManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardHoveredSignature, APDCardActor*, HoveredActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardUnhoveredSignature, APDCardActor*, UnhoveredActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardClickedSignature, APDCardActor*, ClickedActor);

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

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardClickedSignature OnCardClicked;

private:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<APDCardActor> CardActorClass;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerHandStartLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerHandCardPadding;

    UPROPERTY(EditDefaultsOnly)
    FVector LocationCardLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerShipsStartLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerShipsCardPadding;

    UPROPERTY(EditDefaultsOnly)
    FVector EnemyShipsStartLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector EnemyShipsCardPadding;

    UPROPERTY()
    UPDEventManager* EventManager;

    UPROPERTY()
    TMap<int64, APDCardActor*> Cards;

    UPROPERTY()
    TArray<APDCardActor*> HandCards;

    UPROPERTY()
    TArray<APDCardActor*> LocalPlayerCards;

    UPROPERTY()
    APDCardActor* CurrentLocationCard;

    UPROPERTY()
    TArray<APDCardActor*> EnemyCards;

    UFUNCTION()
    void OnPlayerHandChanged(const UObject* EventData);

    UFUNCTION()
    void OnCurrentLocationChanged(const UObject* EventData);

    UFUNCTION()
    void OnCardPlayed(const UObject* EventData);

    UFUNCTION()
    void OnBeginCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnClicked(AActor* TouchedActor, FKey ButtonPressed);

    void InitCardActor(APDCardActor* CardActor, int64 EntityId, const FString& CardId);
};
