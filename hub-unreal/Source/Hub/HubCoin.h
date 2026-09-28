#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HubCoin.generated.h"

class USphereComponent;
class UStaticMeshComponent;

/** A coin: +5 credits, +10 XP, remembered per map so it stays collected. */
UCLASS()
class HUB_API AHubCoin : public AActor
{
	GENERATED_BODY()
public:
	AHubCoin();
	UPROPERTY(VisibleAnywhere) USphereComponent* Trigger;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Mesh;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void OnOverlap(UPrimitiveComponent* Comp, AActor* Other, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& Sweep);
	FName CoinId() const;
};
