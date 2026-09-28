#pragma once

#include "CoreMinimal.h"
#include "HubInteractable.h"
#include "HubKiosk.generated.h"

class AHubCharacter;

USTRUCT(BlueprintType)
struct FHubShopItem
{
	GENERATED_BODY()
	/** a feature name (cape, wings, halo...) or "fin:<material>" for a finish */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Price = 30;
};

/** Outfitters: buy once, keep forever, wear or remove any time (blueprint section 6). The list UI is a widget bound in the editor. */
UCLASS()
class HUB_API AHubKiosk : public AHubInteractable
{
	GENERATED_BODY()
public:
	AHubKiosk();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hub") TArray<FHubShopItem> Items;

	virtual void Interact_Implementation(AHubCharacter* Player) override;
	/** Bound in the editor: show the shop widget for this player. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hub") void OpenShop(AHubCharacter* Player);
	/** Buy (if not owned) then toggle wearing. Returns the new "worn" state. */
	UFUNCTION(BlueprintCallable, Category = "Hub") bool BuyOrToggle(AHubCharacter* Player, FName ItemId);
	UFUNCTION(BlueprintPure, Category = "Hub") static bool IsWorn(AHubCharacter* Player, FName ItemId);
};
