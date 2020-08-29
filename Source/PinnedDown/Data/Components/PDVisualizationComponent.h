#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "PDVisualizationComponent.generated.h"

UCLASS(BlueprintType)
class PINNEDDOWN_API UPDVisualizationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    FText GetCardName() const;

    UFUNCTION(BlueprintPure)
    TSoftObjectPtr<UTexture2D> GetCardImage() const;

    UFUNCTION(BlueprintPure)
    FText GetCardGameText() const;

    void SetCardName(const FText& InName);
    void SetCardImage(TSoftObjectPtr<UTexture2D> InImage);
    void SetCardGameText(const FText& InGameText);

private:
    UPROPERTY(VisibleAnywhere)
    FText Name;

    UPROPERTY(VisibleAnywhere)
    TSoftObjectPtr<UTexture2D> Image;

    UPROPERTY(VisibleAnywhere)
    FText GameText;
};
