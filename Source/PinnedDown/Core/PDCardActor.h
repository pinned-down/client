#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "UI/PDCardAnimation.h"

#include "PDCardActor.generated.h"

class UPDAbilitiesComponent;
class UPDAbilityEffectsComponent;
class UPDAssignmentComponent;
class UPDAttachmentComponent;
class UPDDistanceComponent;
class UPDGameplayTagsComponent;
class UPDOwnerComponent;
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

    UFUNCTION(BlueprintImplementableEvent)
    void OnShowSmallVersionChanged(bool bInShowSmallVersion);

    UFUNCTION(BlueprintPure)
    int64 GetEntityId() const;

    UFUNCTION(BlueprintPure)
    FName GetCardId() const;

    FPDCardAnimation GetCardAnimation() const;
    void SetCardAnimation(FPDCardAnimation InCardAnimation);

    UFUNCTION(BlueprintPure)
    bool ShowSmallVersion() const;

    void SetShowSmallVersion(bool bInShowSmallVersion);

private:
    UPROPERTY(VisibleAnywhere)
    int64 EntityId;

    UPROPERTY(VisibleAnywhere)
    FName CardId;

    UPROPERTY(VisibleAnywhere)
    bool bShowSmallVersion;
    
    UPROPERTY(VisibleAnywhere)
    FPDCardAnimation CardAnimation;

    UPROPERTY(VisibleAnywhere)
    UPDAbilitiesComponent* AbilitiesComponent;

    UPROPERTY(VisibleAnywhere)
    UPDAbilityEffectsComponent* AbilityEffectsComponent;

    UPROPERTY(VisibleAnywhere)
    UPDAssignmentComponent* AssignmentComponent;

    UPROPERTY(VisibleAnywhere)
    UPDAttachmentComponent* AttachmentComponent;

    UPROPERTY(VisibleAnywhere)
    UPDDistanceComponent* DistanceComponent;

    UPROPERTY(VisibleAnywhere)
    UPDGameplayTagsComponent* GameplayTagsComponent;

    UPROPERTY(VisibleAnywhere)
    UPDOwnerComponent* OwnerComponent;

    UPROPERTY(VisibleAnywhere)
    UPDPowerComponent* PowerComponent;

    UPROPERTY(VisibleAnywhere)
    UPDStructureComponent* StructureComponent;

    UPROPERTY(VisibleAnywhere)
    UPDThreatComponent* ThreatComponent;

    UPROPERTY(VisibleAnywhere)
    UPDVisualizationComponent* VisualizationComponent;
};
