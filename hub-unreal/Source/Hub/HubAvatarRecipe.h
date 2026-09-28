#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HubAvatarRecipe.generated.h"

/** "Describe your avatar and the game builds it" (UNIVERSE-BLUEPRINT.md section 5a).
 *  The recipe is the contract between the words and whatever mesh setup the editor binds to it
 *  (a MetaHuman with material parameters, a modular character, a creature). */

UENUM(BlueprintType)
enum class EHubBody : uint8 { Humanoid, Robot, Beast, Blob };

UENUM(BlueprintType)
enum class EHubBuild : uint8 { Slim, Normal, Heavy, Huge };

UENUM(BlueprintType)
enum class EHubHead : uint8 { Helmet, Visor, Bare, Animal, Skull, Screen };

UENUM(BlueprintType)
enum class EHubMaterial : uint8 { Cloth, Matte, Plate, Chrome, Glass, Fur, Jelly, Stone, Neon };

UENUM(BlueprintType)
enum class EHubEyes : uint8 { Visor, Dots, Wide, Slits, One };

USTRUCT(BlueprintType)
struct FHubAvatarRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHubBody Body = EHubBody::Humanoid;
	/** metres, 0.6 to 2.4 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Height = 1.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHubBuild Build = EHubBuild::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHubHead Head = EHubHead::Visor;
	/** ears, snout, horns, tail, wings, cape, hood, backpack, jetpack, sword, staff, antenna, halo, crown, mask, spikes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> Features;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHubMaterial Material = EHubMaterial::Plate;
	/** none, stripes, plates, circuits, camo, checks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Pattern = TEXT("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor MainColour = FLinearColor(0.12f, 0.16f, 0.27f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor SecondColour = FLinearColor(0.93f, 0.93f, 0.95f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor TrimColour = FLinearColor(0.36f, 0.88f, 0.9f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor GlowColour = FLinearColor(0.36f, 0.88f, 0.9f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EHubEyes Eyes = EHubEyes::Visor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor EyeGlow = FLinearColor(0.36f, 0.88f, 0.9f);
	/** the words this recipe came from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Description;

	bool HasFeature(FName F) const { return Features.Contains(F); }
	void AddFeature(FName F) { if (!Features.Contains(F)) Features.Add(F); }
};

UCLASS()
class HUB_API UHubAvatarLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Path 1 of the blueprint: an on-device parser. Always works, no network. */
	UFUNCTION(BlueprintCallable, Category = "Hub|Avatar")
	static FHubAvatarRecipe ParseDescription(const FString& Text);

	/** One-line readback, e.g. "tall chrome humanoid, with cape, sword; eyes: slits" */
	UFUNCTION(BlueprintPure, Category = "Hub|Avatar")
	static FString DescribeRecipe(const FHubAvatarRecipe& Recipe);

	/** A random description from the built-in list, for NPCs. */
	UFUNCTION(BlueprintCallable, Category = "Hub|Avatar")
	static FString RandomLook(int32 Seed);
};
