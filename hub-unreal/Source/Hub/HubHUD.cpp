#include "HubHUD.h"
#include "HubCharacter.h"
#include "HubProgress.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "Engine/World.h"

void AHubHUD::DrawHUD()
{
	Super::DrawHUD();
	AHubCharacter* P = Cast<AHubCharacter>(GetOwningPawn());
	if (!P && GetOwningPlayerController())
	{
		// while riding, the view target is the bike and the character hangs off it; find it either way
		TArray<AActor*> Attached;
		if (AActor* View = GetOwningPlayerController()->GetViewTarget()) View->GetAttachedActors(Attached);
		for (AActor* A : Attached) if (AHubCharacter* C = Cast<AHubCharacter>(A)) { P = C; break; }
		if (!P) if (AHubCharacter* C = Cast<AHubCharacter>(GetOwningPawn())) P = C;
	}
	if (!P || !P->Progress) return;
	UFont* Font = GEngine ? GEngine->GetMediumFont() : nullptr;
	const float Scale = Canvas ? FMath::Max(1.f, Canvas->SizeY / 720.f) : 1.f;
	const FLinearColor Ink(0.95f, 0.94f, 1.f), Muted(0.72f, 0.7f, 0.88f), Gold(1.f, 0.82f, 0.4f), Cyan(0.36f, 0.88f, 0.9f), Panel(0.05f, 0.05f, 0.16f, 0.72f);
	const UHubProgress* Pr = P->Progress;

	DrawRect(Panel, 16.f * Scale, 16.f * Scale, 290.f * Scale, 92.f * Scale);
	DrawText(Pr->PlayerName, Ink, 26.f * Scale, 22.f * Scale, Font, Scale * 1.1f);
	DrawText(FString::Printf(TEXT("Level %d"), Pr->Level()), Cyan, 210.f * Scale, 22.f * Scale, Font, Scale);
	DrawRect(FLinearColor(1.f, 1.f, 1.f, 0.14f), 26.f * Scale, 48.f * Scale, 270.f * Scale, 6.f * Scale);
	const float HpFrac = FMath::Clamp(Pr->HP / Pr->MaxHP(), 0.f, 1.f);
	DrawRect(HpFrac < 0.3f ? FLinearColor(1.f, 0.3f, 0.3f) : FLinearColor(0.5f, 0.95f, 0.5f), 26.f * Scale, 48.f * Scale, 270.f * Scale * HpFrac, 6.f * Scale);
	DrawText(FString::Printf(TEXT("HP %d / %d"), FMath::CeilToInt(Pr->HP), FMath::CeilToInt(Pr->MaxHP())), Muted, 26.f * Scale, 58.f * Scale, Font, Scale * 0.85f);
	DrawText(FString::Printf(TEXT("%d credits"), Pr->Credits), Gold, 26.f * Scale, 80.f * Scale, Font, Scale);
	DrawText(GetWorld() ? GetWorld()->GetMapName() : TEXT(""), Muted, 180.f * Scale, 80.f * Scale, Font, Scale * 0.85f);

	if (!P->TrialStatus.IsEmpty()) { DrawRect(Panel, 16.f * Scale, 116.f * Scale, 290.f * Scale, 30.f * Scale); DrawText(P->TrialStatus, Gold, 26.f * Scale, 122.f * Scale, Font, Scale); }
	if (!P->InteractPrompt.IsEmpty()) { DrawRect(Panel, Canvas->SizeX * 0.5f - 160.f * Scale, Canvas->SizeY - 120.f * Scale, 320.f * Scale, 30.f * Scale); DrawText(P->InteractPrompt, Ink, Canvas->SizeX * 0.5f - 150.f * Scale, Canvas->SizeY - 114.f * Scale, Font, Scale); }
	if (GetWorld() && GetWorld()->GetTimeSeconds() - P->LastToastTime < 3.f && !P->LastToast.IsEmpty())
	{
		DrawRect(Panel, Canvas->SizeX * 0.5f - 260.f * Scale, Canvas->SizeY - 70.f * Scale, 520.f * Scale, 32.f * Scale);
		DrawText(P->LastToast, Ink, Canvas->SizeX * 0.5f - 250.f * Scale, Canvas->SizeY - 64.f * Scale, Font, Scale);
	}
}
