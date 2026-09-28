#include "HubCoin.h"
#include "HubCharacter.h"
#include "HubProgress.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

AHubCoin::AHubCoin()
{
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->InitSphereRadius(90.f);
	Trigger->SetCollisionProfileName(TEXT("HubInteract"));
	Trigger->SetGenerateOverlapEvents(true);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Trigger);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHubCoin::OnOverlap);
}

FName AHubCoin::CoinId() const
{
	return FName(*FString::Printf(TEXT("%s:%s"), *GetWorld()->GetMapName(), *GetName()));
}

void AHubCoin::BeginPlay()
{
	Super::BeginPlay();
	// already collected in an earlier visit: remove
	if (AHubCharacter* P = Cast<AHubCharacter>(GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->GetPawn() : nullptr))
	{
		if (P->Progress && P->Progress->HasCoin(CoinId())) Destroy();
	}
}

void AHubCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Mesh) Mesh->AddLocalRotation(FRotator(0.f, 140.f * DeltaTime, 0.f));
}

void AHubCoin::OnOverlap(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	AHubCharacter* P = Cast<AHubCharacter>(Other); if (!P || !P->Progress) return;
	P->Progress->TakeCoin(CoinId());
	P->Toast(TEXT("+5 credits  +10 XP"));
	Destroy();
}
