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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerDrawDeckHoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerDrawDeckUnhoveredSignature);

UCLASS(BlueprintType, Blueprintable, meta=(Inject))
class PINNEDDOWN_API UPDCardActorManager : public UObject
{
    GENERATED_BODY()

public:
    UPDCardActorManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void Init();

    UFUNCTION(BlueprintPure)
    APDCardActor* GetCardActor(int64 EntityId) const;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardHoveredSignature OnCardHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardUnhoveredSignature OnCardUnhovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDrawDeckHoveredSignature OnDrawDeckHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDrawDeckUnhoveredSignature OnDrawDeckUnhovered;

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

    UPROPERTY(EditDefaultsOnly)
    FVector AssignedCardOffset;

    UPROPERTY(EditDefaultsOnly)
    FVector AttachedCardOffset;

    UPROPERTY(EditDefaultsOnly)
    FVector DrawDeckLocation;

    UPROPERTY(EditDefaultsOnly)
    FRotator DrawDeckRotation;

    UPROPERTY(meta=(Inject))
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

    UPROPERTY()
    TArray<APDCardActor*> DamageCards;

    UPROPERTY()
    APDCardActor* TopDrawDeckCard;

    UFUNCTION()
    void OnPlayerDrawDeckSizeChanged(const UObject* EventData);

    UFUNCTION()
    void OnPlayerHandChanged(const UObject* EventData);

    UFUNCTION()
    void OnCardPlayed(const UObject* EventData);

    UFUNCTION()
    void OnStarshipAssigned(const UObject* EventData);

    UFUNCTION()
    void OnStarshipDamaged(const UObject* EventData);

    UFUNCTION()
    void OnCardRemoved(const UObject* EventData);

    UFUNCTION()
    void OnStarshipPowerChanged(const UObject* EventData);

    UFUNCTION()
    void OnBeginCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnBeginCursorOverDrawDeck(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOverDrawDeck(AActor* TouchedActor);

    UFUNCTION()
    void OnClicked(AActor* TouchedActor, FKey ButtonPressed);

    void InitCardActor(APDCardActor* CardActor, int64 EntityId, const FString& CardId);
};
