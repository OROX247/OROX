#include "HubProgress.h"
#include "HubSaveGame.h"
#include "Hub.h"
#include "Kismet/GameplayStatics.h"

UHubProgress::UHubProgress()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHubProgress::BeginPlay()
{
	Super::BeginPlay();
	LoadNow();
}

void UHubProgress::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// HP refills in safe realms, never in danger zones (health kits matter there)
	if (!bDangerRealm && HP < MaxHP()) { HP = FMath::Min(MaxHP(), HP + 12.f * DeltaTime); }
}

void UHubProgress::Reward(int32 InXP, int32 InCredits)
{
	const int32 Before = Level();
	XP += InXP; Credits += InCredits;
	const int32 After = Level();
	if (After > Before) { HP += 5.f * (After - Before); Toast(FString::Printf(TEXT("Level %d reached"), After)); }
	OnChanged.Broadcast(); SaveNow();
}

bool UHubProgress::Spend(int32 Amount)
{
	if (Credits < Amount) { Toast(TEXT("Not enough credits. Coins turn into credits.")); return false; }
	Credits -= Amount; OnChanged.Broadcast(); SaveNow(); return true;
}

float UHubProgress::Hurt(float Amount, const FString& Why)
{
	if (Amount <= 0.f || !bDangerRealm) return 0.f;
	HP = FMath::Max(0.f, HP - Amount); OnChanged.Broadcast();
	if (HP <= 0.f) ZeroOut(Why);
	return Amount;
}

void UHubProgress::Heal(float Amount) { HP = FMath::Min(MaxHP(), HP + Amount); OnChanged.Broadcast(); }

void UHubProgress::TakeCoin(FName CoinId)
{
	if (CollectedCoins.Contains(CoinId)) return;
	CollectedCoins.Add(CoinId); Reward(10, 5);
}

void UHubProgress::SetRecipeFromWords(const FString& Words)
{
	Recipe = UHubAvatarLibrary::ParseDescription(Words); OnChanged.Broadcast(); SaveNow();
}

void UHubProgress::ZeroOut(const FString& Why)
{
	const int32 Dropped = Credits; const TArray<FName> DroppedItems = OwnedItems;
	Credits = 0; OwnedItems.Empty(); XP = 0; HP = MaxHP();
	Toast(FString::Printf(TEXT("ZEROED OUT (%s). Your bundle is where you fell."), *Why));
	OnZeroedOut(Dropped, DroppedItems);
	OnChanged.Broadcast(); SaveNow();
	// respawn on the Spaceport
	UGameplayStatics::OpenLevel(this, TEXT("/Game/Maps/HubSpaceport"));
}

void UHubProgress::SaveNow()
{
	UHubSaveGame* S = UHubSaveGame::LoadOrCreate(); if (!S) return;
	S->PlayerName = PlayerName; S->Credits = Credits; S->XP = XP; S->HP = HP; S->Recipe = Recipe; S->OwnedItems = OwnedItems;
	S->CollectedCoins = CollectedCoins; S->Shards = Shards; S->BestTimes = BestTimes; S->Save();
}

void UHubProgress::LoadNow()
{
	UHubSaveGame* S = UHubSaveGame::LoadOrCreate(); if (!S) return;
	PlayerName = S->PlayerName; Credits = S->Credits; XP = S->XP; HP = S->HP > 0.f ? S->HP : MaxHP(); Recipe = S->Recipe; OwnedItems = S->OwnedItems;
	CollectedCoins = S->CollectedCoins; Shards = S->Shards; BestTimes = S->BestTimes;
	OnChanged.Broadcast();
}
