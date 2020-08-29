#include "PDCardSet.h"

#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "Core/PDLog.h"

void UPDCardSet::LoadFromDisk()
{
    FString CardSetPath = FPaths::ProjectContentDir() / TEXT("Data/PinnedDown.json");

    FString JsonString;
    FFileHelper::LoadFileToString(JsonString, *CardSetPath);

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    FJsonSerializer::Deserialize(JsonReader, JsonObject);

    Hash = JsonObject->GetStringField(TEXT("hash"));

    TArray<TSharedPtr<FJsonValue>> CardValues = JsonObject->GetArrayField(TEXT("records"));

    for (TSharedPtr<FJsonValue> CardValue : CardValues)
    {
        TSharedPtr<FJsonObject> CardObject = CardValue->AsObject();

        FString Id = CardObject->GetStringField(TEXT("id"));
        TSharedPtr<FJsonObject> Attributes = CardObject->GetObjectField(TEXT("attributes"));

        Cards.Add(FName(Id), Attributes);
    }
}

FString UPDCardSet::GetHash() const
{
    return Hash;
}

int32 UPDCardSet::Num() const
{
    return Cards.Num();
}

TArray<FName> UPDCardSet::GetCardIds() const
{
    TArray<FName> CardIds;
    Cards.GetKeys(CardIds);
    return CardIds;
}

TSharedPtr<FJsonObject> UPDCardSet::GetCardAttributes(const FName& CardId) const
{
    return Cards.FindRef(CardId);
}
