#include "PDAbilitiesComponent.h"

#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Kismet/GameplayStatics.h"

#include "Core/PDGameInstance.h"
#include "Data/PDCardSet.h"

TArray<FString> UPDAbilitiesComponent::GetAbilityIds() const
{
    return Abilities;
}

TArray<FPDAbility> UPDAbilitiesComponent::GetAbilities() const
{
    TArray<FPDAbility> AbilityDataArray;

    UPDGameInstance* GameInstance = Cast<UPDGameInstance>(UGameplayStatics::GetGameInstance(this));

    if (!IsValid(GameInstance))
    {
        return AbilityDataArray;
    }

    UPDCardSet* CardSet = GameInstance->GetCardSet();

    if (!IsValid(CardSet))
    {
        return AbilityDataArray;
    }

    for (const FString& AbilityId : Abilities)
    {
        TSharedPtr<FJsonObject> CardAttributes = CardSet->GetCardAttributes(FName(AbilityId));

        if (CardAttributes != nullptr)
        {
            FPDAbility AbilityData;
            FJsonObjectConverter::JsonObjectToUStruct(CardAttributes.ToSharedRef(), &AbilityData);
            AbilityDataArray.Add(AbilityData);
        }
    }

    return AbilityDataArray;
}
