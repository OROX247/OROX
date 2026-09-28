#include "HubTimeTrial.h"
#include "HubCharacter.h"
#include "HubProgress.h"
#include "Components/SphereComponent.h"

AHubTimeTrial::AHubTimeTrial()
{
	PrimaryActorTick.bCanEverTick = true;
	Pad = CreateDefaultSubobject<USphereComponent>(TEXT("Pad"));
	SetRootComponent(Pad);
	Pad->InitSphereRadius(200.f);
	Pad->SetCollisionProfileName(TEXT("HubInteract"));
	Pad->SetGenerateOverlapEvents(true);
	Pad->OnComponentBeginOverlap.AddDynamic(this, &AHubTimeTrial::OnPad);
}

void AHubTimeTrial::BeginPlay() { Super::BeginPlay(); ShowRings(false); }

void AHubTimeTrial::ShowRings(bool bShow)
{
	for (int32 i = 0; i < Rings.Num(); i++) if (Rings[i]) { Rings[i]->SetActorHiddenInGame(!bShow); Rings[i]->SetActorEnableCollision(false); }
}

void AHubTimeTrial::OnPad(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	AHubCharacter* P = Cast<AHubCharacter>(Other);
	if (!P) { if (AActor* Owner = Other ? Other->GetAttachParentActor() : nullptr) P = Cast<AHubCharacter>(Owner); }
	if (P && !bActive) Start(P);
}

void AHubTimeTrial::Start(AHubCharacter* P)
{
	if (Rings.Num() == 0) return;
	Player = P; bActive = true; Index = 0; Elapsed = 0.f; ShowRings(true);
	P->Toast(FString::Printf(TEXT("Time trial: ride through the %d rings in order. Par %.0fs"), Rings.Num(), ParSeconds));
}

void AHubTimeTrial::Finish(bool bDone)
{
	bActive = false; ShowRings(false);
	if (!Player) return;
	Player->TrialStatus.Empty();
	if (!bDone) { Player->Toast(TEXT("Time trial cancelled")); Player = nullptr; return; }
	UHubProgress* Pr = Player->Progress;
	const float* Best = Pr->BestTimes.Find(TrialId); const bool bNewBest = !Best || Elapsed < *Best;
	if (bNewBest) Pr->BestTimes.Add(TrialId, Elapsed);
	const bool bUnderPar = Elapsed <= ParSeconds;
	const int32 Credits = 60 + (bUnderPar ? 40 : 0) + (bNewBest ? 20 : 0);
	Pr->Reward(120, Credits);
	Player->Toast(FString::Printf(TEXT("Finished in %.1fs%s%s   +120 XP  +%d credits"), Elapsed, bUnderPar ? TEXT(" - under par") : TEXT(""), bNewBest ? TEXT(" - new best") : TEXT(""), Credits));
	OnFinished(Elapsed, bUnderPar, bNewBest);
	Player = nullptr;
}

void AHubTimeTrial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bActive || !Player) return;
	Elapsed += DeltaTime;
	Player->TrialStatus = FString::Printf(TEXT("Ring %d / %d  %.1fs"), FMath::Min(Index + 1, Rings.Num()), Rings.Num(), Elapsed);
	// the player's position while riding is the bike's, since the character is attached to it
	const FVector Pos = Player->GetActorLocation();
	if (AActor* R = Rings.IsValidIndex(Index) ? Rings[Index] : nullptr)
	{
		if (FVector::Dist(R->GetActorLocation(), Pos) < RingRadius)
		{
			R->SetActorHiddenInGame(true); OnRingPassed(Index); Index++;
			if (Index >= Rings.Num()) Finish(true);
		}
	}
	if (Elapsed > 150.f) Finish(false);
}
