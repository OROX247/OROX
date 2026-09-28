#include "HubKiosk.h"
#include "HubCharacter.h"
#include "HubProgress.h"

AHubKiosk::AHubKiosk()
{
	Prompt = TEXT("Outfitters · E to browse gear");
	const TCHAR* Names[] = { TEXT("cape"), TEXT("hood"), TEXT("wings"), TEXT("halo"), TEXT("crown"), TEXT("horns"), TEXT("antenna"), TEXT("spikes"), TEXT("tail"), TEXT("backpack"), TEXT("jetpack"), TEXT("sword"), TEXT("staff"), TEXT("mask") };
	const int32 Prices[] = { 30, 20, 60, 40, 50, 25, 15, 20, 20, 25, 45, 35, 35, 15 };
	for (int32 i = 0; i < UE_ARRAY_COUNT(Names); i++) { FHubShopItem It; It.Id = Names[i]; It.Name = FString(Names[i]); It.Name[0] = FChar::ToUpper(It.Name[0]); It.Price = Prices[i]; Items.Add(It); }
	const TCHAR* Fin[] = { TEXT("chrome"), TEXT("neon"), TEXT("glass"), TEXT("stone"), TEXT("jelly"), TEXT("fur") };
	const int32 FinPrices[] = { 80, 60, 90, 40, 50, 45 };
	for (int32 i = 0; i < UE_ARRAY_COUNT(Fin); i++) { FHubShopItem It; It.Id = FName(*FString::Printf(TEXT("fin:%s"), Fin[i])); It.Name = FString(Fin[i]) + TEXT(" finish"); It.Name[0] = FChar::ToUpper(It.Name[0]); It.Price = FinPrices[i]; Items.Add(It); }
}

void AHubKiosk::Interact_Implementation(AHubCharacter* Player) { OpenShop(Player); }

static EHubMaterial MaterialFromName(const FString& N)
{
	if (N == TEXT("chrome")) return EHubMaterial::Chrome; if (N == TEXT("neon")) return EHubMaterial::Neon; if (N == TEXT("glass")) return EHubMaterial::Glass;
	if (N == TEXT("stone")) return EHubMaterial::Stone; if (N == TEXT("jelly")) return EHubMaterial::Jelly; if (N == TEXT("fur")) return EHubMaterial::Fur; return EHubMaterial::Plate;
}

bool AHubKiosk::IsWorn(AHubCharacter* Player, FName ItemId)
{
	if (!Player || !Player->Progress) return false;
	const FString S = ItemId.ToString();
	if (S.StartsWith(TEXT("fin:"))) return Player->Progress->Recipe.Material == MaterialFromName(S.Mid(4));
	return Player->Progress->Recipe.HasFeature(ItemId);
}

bool AHubKiosk::BuyOrToggle(AHubCharacter* Player, FName ItemId)
{
	if (!Player || !Player->Progress) return false;
	UHubProgress* Pr = Player->Progress;
	const FHubShopItem* Item = Items.FindByPredicate([&](const FHubShopItem& I) { return I.Id == ItemId; }); if (!Item) return false;
	const bool bOwned = Pr->OwnedItems.Contains(ItemId);
	if (!bOwned) { if (!Pr->Spend(Item->Price)) return false; Pr->OwnedItems.Add(ItemId); Pr->Reward(10, 0); Player->Toast(FString::Printf(TEXT("Bought: %s for %d credits"), *Item->Name, Item->Price)); }
	const FString S = ItemId.ToString();
	bool bWorn;
	if (S.StartsWith(TEXT("fin:")))
	{
		const EHubMaterial M = MaterialFromName(S.Mid(4));
		if (bOwned && Pr->Recipe.Material == M) { Pr->Recipe.Material = UHubAvatarLibrary::ParseDescription(Pr->Recipe.Description).Material; bWorn = false; }
		else { Pr->Recipe.Material = M; bWorn = true; }
	}
	else
	{
		if (bOwned && Pr->Recipe.HasFeature(ItemId)) { Pr->Recipe.Features.Remove(ItemId); bWorn = false; }
		else { Pr->Recipe.AddFeature(ItemId); bWorn = true; }
	}
	Pr->SaveNow(); Player->ApplyRecipe(Pr->Recipe);
	return bWorn;
}
