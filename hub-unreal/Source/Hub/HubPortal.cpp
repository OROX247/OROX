#include "HubPortal.h"
#include "HubCharacter.h"
#include "HubProgress.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AHubPortal::AHubPortal()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->SetBoxExtent(FVector(60.f, 200.f, 200.f));
	Trigger->SetCollisionProfileName(TEXT("HubInteract"));
	Trigger->SetGenerateOverlapEvents(true);
	Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));
	Ring->SetupAttachment(Trigger);
	Ring->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHubPortal::OnOverlap);
}

void AHubPortal::OnOverlap(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	AHubCharacter* P = Cast<AHubCharacter>(Other); if (!P || TargetMap.IsNull()) return;
	if (Fare > 0 && !P->Progress->Spend(Fare)) return;
	P->Progress->SaveNow();
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, TargetMap);
}
