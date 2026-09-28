#include "HubGameMode.h"
#include "HubCharacter.h"
#include "HubProgress.h"
#include "HubHUD.h"
#include "GameFramework/PlayerController.h"

AHubGameMode::AHubGameMode()
{
	DefaultPawnClass = AHubCharacter::StaticClass();
	HUDClass = AHubHUD::StaticClass();
}

void AHubGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (AHubCharacter* P = Cast<AHubCharacter>(NewPlayer ? NewPlayer->GetPawn() : nullptr))
	{
		P->bTechWorks = bTechWorks;
		if (P->Progress) P->Progress->bDangerRealm = bDangerRealm;
	}
}
