#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HubTimeTrial.generated.h"

class USphereComponent;
class AHubCharacter;

/** The first quest: a pad starts it, ride through the rings in order against the clock (blueprint section 7). */
UCLASS()
class HUB_API AHubTimeTrial : public AActor
{
	GENERATED_BODY()
public:
	AHubTimeTrial();

	UPROPERTY(VisibleAnywhere) USphereComponent* Pad;
	/** ring actors placed in the map, in order; they are shown while a trial runs and hidden otherwise */
	UPROPERTY(EditAnywhere, Category = "Hub") TArray<AActor*> Rings;
	UPROPERTY(EditAnywhere, Category = "Hub") FName TrialId = TEXT("hub");
	UPROPERTY(EditAnywhere, Category = "Hub") float ParSeconds = 42.f;
	UPROPERTY(EditAnywhere, Category = "Hub") float RingRadius = 260.f;

	UPROPERTY(BlueprintReadOnly, Category = "Hub") bool bActive = false;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") int32 Index = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") float Elapsed = 0.f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void OnPad(UPrimitiveComponent* Comp, AActor* Other, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& Sweep);
	void Start(AHubCharacter* P);
	void Finish(bool bDone);
	/** Blueprint hooks for effects and sound */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hub") void OnRingPassed(int32 RingIndex);
	UFUNCTION(BlueprintImplementableEvent, Category = "Hub") void OnFinished(float Seconds, bool bUnderPar, bool bNewBest);

protected:
	UPROPERTY() AHubCharacter* Player = nullptr;
	void ShowRings(bool bShow);
};
