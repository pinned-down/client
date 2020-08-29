#include "PDVisualizationComponent.h"

FText UPDVisualizationComponent::GetCardName() const
{
    return Name;
}

TSoftObjectPtr<UTexture2D> UPDVisualizationComponent::GetCardImage() const
{
    return Image;
}

FText UPDVisualizationComponent::GetCardGameText() const
{
    return GameText;
}

void UPDVisualizationComponent::SetCardName(const FText& InName)
{
    Name = InName;
}

void UPDVisualizationComponent::SetCardImage(TSoftObjectPtr<UTexture2D> InImage)
{
    Image = InImage;
}

void UPDVisualizationComponent::SetCardGameText(const FText& InGameText)
{
    GameText = InGameText;
}
