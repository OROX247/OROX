#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HubPortal.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

/** Walk in, arrive in another realm (another map). Fares follow the sector cube (blueprint section 4). */
UCLASS()
class HUB_API AHubPortal : public AActor
{
	GENERATED_BODY()
public:
	AHubPortal();

	UPROPERTY(VisibleAnywhere) UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Ring;

	/** the realm's map, e.g. /Game/Maps/GlassDunes */
	UPROPERTY(EditAnywhere, Category = "Hub") TSoftObjectPtr<UWorld> TargetMap;
	UPROPERTY(EditAnywhere, Category = "Hub") FString TargetName = TEXT("Glass Dunes");
	/** 0 for the Spaceport and for walking through portals; warps from the map screen use sector distance */
	UPROPERTY(EditAnywhere, Category = "Hub") int32 Fare = 0;

	UFUNCTION() void OnOverlap(UPrimitiveComponent* Comp, AActor* Other, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& Sweep);
};
