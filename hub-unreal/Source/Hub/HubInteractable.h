#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HubInteractable.generated.h"

class AHubCharacter;

/** Base for anything the player can use with E: kiosks, bikes, pads, terminals. Subclasses override Interact. */
UCLASS(Abstract, Blueprintable)
class HUB_API AHubInteractable : public AActor
{
	GENERATED_BODY()
public:
	AHubInteractable();

	/** shown as the prompt, e.g. "Hoverbike · E to ride" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hub") FString Prompt = TEXT("E to use");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hub") float UseRange = 300.f;

	UFUNCTION(BlueprintNativeEvent, Category = "Hub") void Interact(AHubCharacter* Player);
	virtual void Interact_Implementation(AHubCharacter* Player) {}
};
