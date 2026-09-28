#include "HubSaveGame.h"
#include "Kismet/GameplayStatics.h"

const FString UHubSaveGame::SlotName = TEXT("HubSave");

UHubSaveGame* UHubSaveGame::LoadOrCreate()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		if (UHubSaveGame* Loaded = Cast<UHubSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0))) return Loaded;
	}
	return Cast<UHubSaveGame>(UGameplayStatics::CreateSaveGameObject(UHubSaveGame::StaticClass()));
}

void UHubSaveGame::Save()
{
	UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}
