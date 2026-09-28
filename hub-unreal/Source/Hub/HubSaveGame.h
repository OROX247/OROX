#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HubAvatarRecipe.h"
#include "HubSaveGame.generated.h"

/** Everything that persists between sessions and realms (levels). */
UCLASS()
class HUB_API UHubSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	static const FString SlotName;

	UPROPERTY() FString PlayerName = TEXT("Player");
	UPROPERTY() int32 Credits = 20;
	UPROPERTY() int32 XP = 0;
	UPROPERTY() float HP = 100.f;
	UPROPERTY() FHubAvatarRecipe Recipe;
	UPROPERTY() TArray<FName> OwnedItems;
	UPROPERTY() TArray<FName> CollectedCoins;   // "Map:CoinName"
	UPROPERTY() TArray<FName> Shards;
	UPROPERTY() TMap<FName, float> BestTimes;
	UPROPERTY() bool bMuted = false;

	static UHubSaveGame* LoadOrCreate();
	void Save();
};
