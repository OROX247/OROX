#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HubAvatarRecipe.h"
#include "HubProgress.generated.h"

class UHubSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHubProgressChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHubToast, const FString&, Message);

/** Credits, XP, level, HP and the zero-out rule (blueprint sections 5 and 6). Lives on the player character. */
UCLASS(ClassGroup = (Hub), meta = (BlueprintSpawnableComponent))
class HUB_API UHubProgress : public UActorComponent
{
	GENERATED_BODY()
public:
	UHubProgress();

	UPROPERTY(BlueprintReadOnly, Category = "Hub") int32 Credits = 20;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") int32 XP = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") float HP = 100.f;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") FString PlayerName = TEXT("Player");
	UPROPERTY(BlueprintReadOnly, Category = "Hub") FHubAvatarRecipe Recipe;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") TArray<FName> OwnedItems;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") TArray<FName> Shards;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") TArray<FName> CollectedCoins;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") TMap<FName, float> BestTimes;

	/** the realm this level represents: does damage apply here? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hub") bool bDangerRealm = false;

	UPROPERTY(BlueprintAssignable) FHubProgressChanged OnChanged;
	UPROPERTY(BlueprintAssignable) FHubToast OnToast;

	UFUNCTION(BlueprintPure, Category = "Hub") int32 Level() const { return 1 + FMath::FloorToInt(FMath::Sqrt(XP / 60.f)); }
	UFUNCTION(BlueprintPure, Category = "Hub") float MaxHP() const { return 100.f + 5.f * (FMath::Min(Level(), 99) - 1); }

	UFUNCTION(BlueprintCallable, Category = "Hub") void Reward(int32 InXP, int32 InCredits);
	UFUNCTION(BlueprintCallable, Category = "Hub") bool Spend(int32 Amount);
	/** Damage only counts in danger realms. Returns the damage applied. */
	UFUNCTION(BlueprintCallable, Category = "Hub") float Hurt(float Amount, const FString& Why);
	UFUNCTION(BlueprintCallable, Category = "Hub") void Heal(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Hub") bool HasCoin(FName CoinId) const { return CollectedCoins.Contains(CoinId); }
	UFUNCTION(BlueprintCallable, Category = "Hub") void TakeCoin(FName CoinId);
	UFUNCTION(BlueprintCallable, Category = "Hub") void SetRecipeFromWords(const FString& Words);

	UFUNCTION(BlueprintCallable, Category = "Hub") void SaveNow();
	UFUNCTION(BlueprintCallable, Category = "Hub") void LoadNow();

	/** Zeroing out: everything carried drops into a bundle, level resets, respawn on the Spaceport (blueprint section 5). */
	UFUNCTION(BlueprintCallable, Category = "Hub") void ZeroOut(const FString& Why);
	/** Blueprint hook: spawn the loot bundle actor / effects here. Bound in the editor. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hub") void OnZeroedOut(int32 DroppedCredits, const TArray<FName>& DroppedItems);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Toast(const FString& Msg) { OnToast.Broadcast(Msg); }
};
