#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HubAvatarRecipe.h"
#include "HubCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UHubProgress;
class AHubHoverbike;
struct FInputActionValue;

/** The player: third-person movement with a double-jump boost, sprint, three camera views, E to interact. */
UCLASS()
class HUB_API AHubCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AHubCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hub") USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hub") UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hub") UHubProgress* Progress;

	/** Input assets. Leave empty and the character builds a default set at runtime (WASD, mouse, Space, Shift, E, V). */
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputMappingContext* Mapping = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputAction* MoveAction = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputAction* LookAction = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputAction* JumpAction = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputAction* SprintAction = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputAction* InteractAction = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Hub|Input") UInputAction* ViewAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "Hub") float WalkSpeed = 600.f;
	UPROPERTY(EditAnywhere, Category = "Hub") float SprintSpeed = 1050.f;
	/** does the jet boost (second jump) work in this realm? false where tech is dead */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hub") bool bTechWorks = true;

	UPROPERTY(BlueprintReadOnly, Category = "Hub") int32 CameraView = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") FString InteractPrompt;
	/** text the HUD shows for the time trial, empty when none */
	UPROPERTY(BlueprintReadWrite, Category = "Hub") FString TrialStatus;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") FString LastToast;
	UPROPERTY(BlueprintReadOnly, Category = "Hub") float LastToastTime = -100.f;

	UFUNCTION(BlueprintCallable, Category = "Hub") void Toast(const FString& Message);
	UFUNCTION(BlueprintCallable, Category = "Hub") void SetCameraView(int32 View);
	/** Bound in the editor: rebuild the visible avatar from the recipe (MetaHuman material parameters, modular parts, creature meshes). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hub") void ApplyRecipe(const FHubAvatarRecipe& Recipe);
	UFUNCTION(BlueprintCallable, Category = "Hub") void DescribeAvatar(const FString& Words);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void NotifyControllerChanged() override;

protected:
	virtual void BeginPlay() override;
	void EnsureInputAssets();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void DoJump(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void CycleView(const FInputActionValue& Value);

	float FallStartZ = 0.f;
	bool bWasFalling = false;
};
