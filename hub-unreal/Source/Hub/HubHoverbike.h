#pragma once

#include "CoreMinimal.h"
#include "HubInteractable.h"
#include "HubHoverbike.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AHubCharacter;
struct FInputActionValue;

/** A hoverbike: E mounts it, W/S throttle, A/D steer, Shift boost, Space hop, E dismounts (blueprint section 4).
 *  Kinematic hover (no Chaos vehicle): it rides a fixed height above whatever the ground trace hits. */
UCLASS()
class HUB_API AHubHoverbike : public AHubInteractable
{
	GENERATED_BODY()
public:
	AHubHoverbike();

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere) USpringArmComponent* Boom;
	UPROPERTY(VisibleAnywhere) UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Hub") float MaxSpeed = 1800.f;
	UPROPERTY(EditAnywhere, Category = "Hub") float BoostSpeed = 2700.f;
	UPROPERTY(EditAnywhere, Category = "Hub") float Accel = 1500.f;
	UPROPERTY(EditAnywhere, Category = "Hub") float HoverHeight = 55.f;
	UPROPERTY(EditAnywhere, Category = "Hub") float TurnRate = 95.f;

	UPROPERTY(BlueprintReadOnly, Category = "Hub") bool bRiding = false;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") float Speed = 0.f;

	virtual void Interact_Implementation(AHubCharacter* Player) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Hub") void Mount(AHubCharacter* Player);
	UFUNCTION(BlueprintCallable, Category = "Hub") void Dismount();

protected:
	UPROPERTY() AHubCharacter* Rider = nullptr;
	UPROPERTY() AController* RiderController = nullptr;
	UPROPERTY() UInputMappingContext* Mapping = nullptr;
	UPROPERTY() UInputAction* ThrottleAction = nullptr;
	UPROPERTY() UInputAction* SteerAction = nullptr;
	UPROPERTY() UInputAction* BoostAction = nullptr;
	UPROPERTY() UInputAction* HopAction = nullptr;
	UPROPERTY() UInputAction* LeaveAction = nullptr;
	float Throttle = 0.f, Steer = 0.f, VerticalVel = 0.f, Lean = 0.f; bool bBoost = false;
	void EnsureInput();
	void OnThrottle(const FInputActionValue& V); void OnThrottleEnd(const FInputActionValue& V);
	void OnSteer(const FInputActionValue& V); void OnSteerEnd(const FInputActionValue& V);
	void OnBoost(const FInputActionValue& V); void OnBoostEnd(const FInputActionValue& V);
	void OnHop(const FInputActionValue& V); void OnLeave(const FInputActionValue& V);
};
