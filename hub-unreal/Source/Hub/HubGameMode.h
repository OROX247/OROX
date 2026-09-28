#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HubGameMode.generated.h"

/** Spawns the Hub character and the code-drawn HUD. Each realm map can subclass this in Blueprint to set its own rules. */
UCLASS()
class HUB_API AHubGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AHubGameMode();
	/** rules line for the realm this map represents (blueprint section 3) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hub") bool bMagicWorks = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hub") bool bTechWorks = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hub") bool bDangerRealm = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hub") int32 Sector = 1;

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
