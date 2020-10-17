#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Core/PDCardActor.h"
#include "Data/PDBattleDestiny.h"
#include "UI/PDCardAnimation.h"

#include "PDCardActorManager.generated.h"

class APDCardActor;
class UPDEventManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardHoveredSignature, APDCardActor*, HoveredActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardUnhoveredSignature, APDCardActor*, UnhoveredActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerCardClickedSignature, APDCardActor*, ClickedActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerDrawDeckHoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerDrawDeckUnhoveredSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerDiscardPileHoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerDiscardPileUnhoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerDiscardPileClickedSignature, const TArray<APDCardActor*>&, DiscardPile);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerLocationCardHoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerLocationCardUnhoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerLocationCardClickedSignature, const TArray<APDCardActor*>&, LocationCards);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPDCardActorManagerThreatModifiersChangedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerActiveAbilityEffectsChangedSignature, APDCardActor*, CardActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPDCardActorManagerBattleDestinyCardRevealedSignature, FPDBattleDestiny, BattleDestiny);

UCLASS(BlueprintType, Blueprintable, meta=(Inject))
class PINNEDDOWN_API APDCardActorManager : public AActor
{
    GENERATED_BODY()

public:
    APDCardActorManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void Init();
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintPure)
    APDCardActor* GetCardActor(int64 EntityId) const;

    UFUNCTION(BlueprintPure)
    int32 GetCardThreat(APDCardActor* CardActor) const;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardHoveredSignature OnCardHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardUnhoveredSignature OnCardUnhovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerCardClickedSignature OnCardClicked;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDrawDeckHoveredSignature OnDrawDeckHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDrawDeckUnhoveredSignature OnDrawDeckUnhovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDiscardPileHoveredSignature OnDiscardPileHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDiscardPileUnhoveredSignature OnDiscardPileUnhovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerDiscardPileClickedSignature OnDiscardPileClicked;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerLocationCardHoveredSignature OnLocationCardHovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerLocationCardUnhoveredSignature OnLocationCardUnhovered;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerLocationCardClickedSignature OnLocationCardClicked;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerThreatModifiersChangedSignature OnThreatModifiersChanged;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerActiveAbilityEffectsChangedSignature OnActiveAbilityEffectsChanged;

    UPROPERTY(BlueprintAssignable)
    FPDCardActorManagerBattleDestinyCardRevealedSignature OnBattleDestinyCardRevealed;

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
    FVector LocationCardPadding;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayerShipsStartLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector AlliedShipsStartLocation;

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

    UPROPERTY(EditDefaultsOnly)
    FVector DiscardPileLocation;

    UPROPERTY(EditDefaultsOnly)
    FVector PlayedCardLocation;

    UPROPERTY(meta=(Inject))
    UPDEventManager* EventManager;

    UPROPERTY()
    TMap<int64, APDCardActor*> Cards;

    UPROPERTY()
    TArray<APDCardActor*> HandCards;

    UPROPERTY()
    TArray<APDCardActor*> LocalPlayerCards;

    UPROPERTY()
    TArray<APDCardActor*> AlliedPlayerCards;

    UPROPERTY()
    TArray<APDCardActor*> LocationCards;

    UPROPERTY()
    TArray<APDCardActor*> EnemyCards;

    UPROPERTY()
    TArray<APDCardActor*> DamageCards;

    UPROPERTY()
    APDCardActor* TopDrawDeckCard;

    UPROPERTY()
    TArray<APDCardActor*> DiscardPileCards;

    UPROPERTY()
    TArray<APDCardActor*> NewCards;

    TMap<FString, int32> ThreatModifiers;

    UFUNCTION()
    void OnPlayerDrawDeckSizeChanged(const UObject* EventData);

    UFUNCTION()
    void OnPlayerDiscardPileChanged(const UObject* EventData);

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
    void NotifyOnThreatModifiersChanged(const UObject* EventData);

    UFUNCTION()
    void OnAbilityEffectActivated(const UObject* EventData);

    UFUNCTION()
    void OnAbilityEffectDeactivated(const UObject* EventData);

    UFUNCTION()
    void OnBattleDestinyDrawn(const UObject* EventData);

    UFUNCTION()
    void OnBeginCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOver(AActor* TouchedActor);

    UFUNCTION()
    void OnClicked(AActor* TouchedActor, FKey ButtonPressed);

    UFUNCTION()
    void OnBeginCursorOverDrawDeck(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOverDrawDeck(AActor* TouchedActor);

    UFUNCTION()
    void OnBeginCursorOverDiscardPile(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOverDiscardPile(AActor* TouchedActor);

    UFUNCTION()
    void OnClickedDiscardPile(AActor* TouchedActor, FKey ButtonPressed);

    UFUNCTION()
    void OnBeginCursorOverLocationCard(AActor* TouchedActor);

    UFUNCTION()
    void OnEndCursorOverLocationCard(AActor* TouchedActor);

    UFUNCTION()
    void OnClickedLocationCard(AActor* TouchedActor, FKey ButtonPressed);

    void InitCardActor(APDCardActor* CardActor, int64 EntityId, const FString& CardId);
    void QueueCardAnimation(APDCardActor* CardActor, FPDCardAnimation CardAnimation);

    bool IsPlayerCard(APDCardActor* CardActor) const;
    bool IsLocalPlayerCard(APDCardActor* CardActor) const;
};
