#include "HubHoverbike.h"
#include "HubCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

AHubHoverbike::AHubHoverbike()
{
	PrimaryActorTick.bCanEverTick = true;
	Prompt = TEXT("Hoverbike · E to ride");
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
	Body->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom"));
	Boom->SetupAttachment(RootComponent);
	Boom->TargetArmLength = 520.f; Boom->SocketOffset = FVector(0.f, 0.f, 120.f); Boom->bEnableCameraLag = true; Boom->CameraLagSpeed = 8.f; Boom->bEnableCameraRotationLag = true; Boom->CameraRotationLagSpeed = 6.f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Boom, USpringArmComponent::SocketName);
	Camera->FieldOfView = 85.f;
}

void AHubHoverbike::Interact_Implementation(AHubCharacter* Player)
{
	if (bRiding) Dismount(); else Mount(Player);
}

void AHubHoverbike::EnsureInput()
{
	if (Mapping) return;
	auto MakeAction = [this](const TCHAR* Name, EInputActionValueType Type) { UInputAction* A = NewObject<UInputAction>(this, Name); A->ValueType = Type; return A; };
	ThrottleAction = MakeAction(TEXT("IA_Throttle"), EInputActionValueType::Axis1D);
	SteerAction = MakeAction(TEXT("IA_Steer"), EInputActionValueType::Axis1D);
	BoostAction = MakeAction(TEXT("IA_Boost"), EInputActionValueType::Boolean);
	HopAction = MakeAction(TEXT("IA_Hop"), EInputActionValueType::Boolean);
	LeaveAction = MakeAction(TEXT("IA_Leave"), EInputActionValueType::Boolean);
	Mapping = NewObject<UInputMappingContext>(this, TEXT("IMC_Bike"));
	auto Negate = [this]() { return NewObject<UInputModifierNegate>(this); };
	Mapping->MapKey(ThrottleAction, EKeys::W); Mapping->MapKey(ThrottleAction, EKeys::S).Modifiers.Add(Negate()); Mapping->MapKey(ThrottleAction, EKeys::Gamepad_LeftY);
	Mapping->MapKey(SteerAction, EKeys::D); Mapping->MapKey(SteerAction, EKeys::A).Modifiers.Add(Negate()); Mapping->MapKey(SteerAction, EKeys::Gamepad_LeftX);
	Mapping->MapKey(BoostAction, EKeys::LeftShift); Mapping->MapKey(HopAction, EKeys::SpaceBar); Mapping->MapKey(LeaveAction, EKeys::E);
}

void AHubHoverbike::Mount(AHubCharacter* Player)
{
	if (!Player || bRiding) return;
	APlayerController* PC = Cast<APlayerController>(Player->GetController()); if (!PC) return;
	Rider = Player; RiderController = PC; bRiding = true; Speed = 0.f;
	EnsureInput();
	// the rider sits on the bike; the bike takes the controls and the camera
	Player->GetCharacterMovement()->DisableMovement();
	Player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Player->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Player->SetActorRelativeLocation(FVector(-20.f, 0.f, 95.f));
	PC->SetViewTargetWithBlend(this, 0.4f);
	if (UEnhancedInputLocalPlayerSubsystem* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) Sub->AddMappingContext(Mapping, 10);
	if (!InputComponent) { InputComponent = NewObject<UEnhancedInputComponent>(this, TEXT("BikeInput")); InputComponent->RegisterComponent(); }
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->ClearActionBindings();
		EIC->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AHubHoverbike::OnThrottle); EIC->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AHubHoverbike::OnThrottleEnd);
		EIC->BindAction(SteerAction, ETriggerEvent::Triggered, this, &AHubHoverbike::OnSteer); EIC->BindAction(SteerAction, ETriggerEvent::Completed, this, &AHubHoverbike::OnSteerEnd);
		EIC->BindAction(BoostAction, ETriggerEvent::Started, this, &AHubHoverbike::OnBoost); EIC->BindAction(BoostAction, ETriggerEvent::Completed, this, &AHubHoverbike::OnBoostEnd);
		EIC->BindAction(HopAction, ETriggerEvent::Started, this, &AHubHoverbike::OnHop);
		EIC->BindAction(LeaveAction, ETriggerEvent::Started, this, &AHubHoverbike::OnLeave);
		PC->PushInputComponent(InputComponent);
	}
	Player->Toast(TEXT("W/S throttle, A/D steer, Shift boost, Space hop, E to get off"));
}

void AHubHoverbike::Dismount()
{
	if (!bRiding) return;
	bRiding = false; Throttle = 0.f; Steer = 0.f; bBoost = false;
	if (APlayerController* PC = Cast<APlayerController>(RiderController))
	{
		if (InputComponent) PC->PopInputComponent(InputComponent);
		if (UEnhancedInputLocalPlayerSubsystem* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) Sub->RemoveMappingContext(Mapping);
		if (Rider) PC->SetViewTargetWithBlend(Rider, 0.3f);
	}
	if (Rider)
	{
		Rider->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Rider->SetActorLocation(GetActorLocation() + GetActorRightVector() * 150.f + FVector(0.f, 0.f, 100.f));
		Rider->SetActorRotation(FRotator(0.f, GetActorRotation().Yaw, 0.f));
		Rider->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Rider->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	Rider = nullptr; RiderController = nullptr;
}

void AHubHoverbike::OnThrottle(const FInputActionValue& V) { Throttle = FMath::Clamp(V.Get<float>(), -1.f, 1.f); }
void AHubHoverbike::OnThrottleEnd(const FInputActionValue&) { Throttle = 0.f; }
void AHubHoverbike::OnSteer(const FInputActionValue& V) { Steer = FMath::Clamp(V.Get<float>(), -1.f, 1.f); }
void AHubHoverbike::OnSteerEnd(const FInputActionValue&) { Steer = 0.f; }
void AHubHoverbike::OnBoost(const FInputActionValue&) { bBoost = true; }
void AHubHoverbike::OnBoostEnd(const FInputActionValue&) { bBoost = false; }
void AHubHoverbike::OnHop(const FInputActionValue&) { if (VerticalVel <= 1.f) VerticalVel = 750.f; }
void AHubHoverbike::OnLeave(const FInputActionValue&) { Dismount(); }

void AHubHoverbike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bRiding) return;
	const float Max = bBoost ? BoostSpeed : MaxSpeed;
	if (Throttle > 0.f) Speed += Accel * Throttle * DeltaTime; else if (Throttle < 0.f) Speed += Accel * 1.5f * Throttle * DeltaTime;
	Speed -= Speed * 0.55f * DeltaTime; Speed = FMath::Clamp(Speed, -600.f, Max);
	const float Grip = FMath::Min(1.f, FMath::Abs(Speed) / 300.f);
	AddActorWorldRotation(FRotator(0.f, Steer * TurnRate * Grip * (Speed < 0.f ? -1.f : 1.f) * DeltaTime, 0.f));
	Lean = FMath::FInterpTo(Lean, -Steer * 18.f * FMath::Min(1.f, FMath::Abs(Speed) / 800.f), DeltaTime, 6.f);
	Body->SetRelativeRotation(FRotator(-FMath::Clamp(Speed / 7000.f, -0.14f, 0.14f) * 57.3f, 0.f, Lean));

	// hover: trace down, ride HoverHeight above the hit; hops fall back under gravity
	FHitResult Hit; const FVector From = GetActorLocation() + FVector(0.f, 0.f, 200.f), To = GetActorLocation() - FVector(0.f, 0.f, 2000.f);
	FCollisionQueryParams Params(SCENE_QUERY_STAT(HubHover), false, this); if (Rider) Params.AddIgnoredActor(Rider);
	const bool bGround = GetWorld()->LineTraceSingleByChannel(Hit, From, To, ECC_Visibility, Params);
	const float TargetZ = (bGround ? Hit.ImpactPoint.Z : GetActorLocation().Z) + HoverHeight + FMath::Sin(GetWorld()->GetTimeSeconds() * 3.f) * 4.f;
	VerticalVel -= 2200.f * DeltaTime;
	float NewZ = GetActorLocation().Z + VerticalVel * DeltaTime;
	if (NewZ < TargetZ) { NewZ = FMath::FInterpTo(NewZ, TargetZ, DeltaTime, 14.f); if (VerticalVel < 0.f) VerticalVel *= 0.2f; }
	const FVector Forward = GetActorForwardVector();
	FVector NewLoc = GetActorLocation() + Forward * Speed * DeltaTime; NewLoc.Z = NewZ;
	FHitResult Sweep; SetActorLocation(NewLoc, true, &Sweep);
	if (Sweep.bBlockingHit) Speed *= 0.4f;
}
