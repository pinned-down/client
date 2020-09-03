#include "PDCardActor.h"

#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Engine/DataTable.h"

#include "Core/PDGameInstance.h"
#include "Data/PDCardSet.h"
#include "Data/PDCardMetadata.h"
#include "Data/Components/PDAssignmentComponent.h"
#include "Data/Components/PDDistanceComponent.h"
#include "Data/Components/PDGameplayTagsComponent.h"
#include "Data/Components/PDOwnerComponent.h"
#include "Data/Components/PDPowerComponent.h"
#include "Data/Components/PDStructureComponent.h"
#include "Data/Components/PDThreatComponent.h"
#include "Data/Components/PDVisualizationComponent.h"

APDCardActor::APDCardActor(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    AssignmentComponent = CreateDefaultSubobject<UPDAssignmentComponent>(TEXT("AssignmentComponent"));
    DistanceComponent = CreateDefaultSubobject<UPDDistanceComponent>(TEXT("DistanceComponent"));
    GameplayTagsComponent = CreateDefaultSubobject<UPDGameplayTagsComponent>(TEXT("GameplayTagsComponent"));
    OwnerComponent = CreateDefaultSubobject<UPDOwnerComponent>(TEXT("OwnerComponent"));
    PowerComponent = CreateDefaultSubobject<UPDPowerComponent>(TEXT("PowerComponent"));
    StructureComponent = CreateDefaultSubobject<UPDStructureComponent>(TEXT("StructureComponent"));
    ThreatComponent = CreateDefaultSubobject<UPDThreatComponent>(TEXT("ThreatComponent"));
    VisualizationComponent = CreateDefaultSubobject<UPDVisualizationComponent>(TEXT("VisualizationComponent"));
}

void APDCardActor::Init(int64 InEntityId, const FName& InCardId)
{
    UPDGameInstance* GameInstance = GetGameInstance<UPDGameInstance>();

    if (!IsValid(GameInstance))
    {
        return;
    }

    EntityId = InEntityId;
    CardId = InCardId;

    // Set metadata.
    UDataTable* CardMetadata = GameInstance->GetCardMetadata();

    if (IsValid(CardMetadata))
    {
        FPDCardMetadata* Data = CardMetadata->FindRow<FPDCardMetadata>(CardId, TEXT("APDCardActor::Init"));

        if (Data != nullptr)
        {
            VisualizationComponent->SetCardName(Data->Name);
            VisualizationComponent->SetCardImage(Data->Image);
            VisualizationComponent->SetCardGameText(Data->GameText);
        }
    }

    // Set attributes.
    UPDCardSet* CardSet = GameInstance->GetCardSet();

    if (IsValid(CardSet))
    {
        TSharedPtr<FJsonObject> CardAttributes = CardSet->GetCardAttributes(CardId);

        if (CardAttributes != nullptr)
        {
            for (UActorComponent* ActorComponent : GetComponents())
            {
                FJsonObjectConverter::JsonObjectToUStruct(CardAttributes.ToSharedRef(), ActorComponent->GetClass(), ActorComponent);
            }
        }
    }

    // Notify listeners.
    OnCardInitialized(EntityId, CardId);
}

int64 APDCardActor::GetEntityId() const
{
    return EntityId;
}
