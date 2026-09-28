#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HubHUD.generated.h"

/** A code-drawn HUD so the game is playable before any widgets exist: name, level, credits, HP bar, prompt, toast, trial timer. */
UCLASS()
class HUB_API AHubHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
};
