#include "HubCharacter.h"
#include "Hub.h"
#include "HubProgress.h"
#include "HubInteractable.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AHubCharacter::AHubCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false; bUseControllerRotationYaw = false; bUseControllerRotationRoll = false;
	UCharacterMovementComponent* Move = GetCharacterMovement();
	Move->bOrientRotationToMovement = true; Move->RotationRate = FRotator(0.f, 500.f, 0.f);
	Move->JumpZVelocity = 700.f; Move->AirControl = 0.35f; Move->MaxWalkSpeed = WalkSpeed;
	Move->BrakingDecelerationWalking = 2000.f; Move->MinAnalogWalkSpeed = 20.f;
	JumpMaxCount = 2;   // the second jump is the jet boost

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 380.f; CameraBoom->bUsePawnControlRotation = true; CameraBoom->bEnableCameraLag = true; CameraBoom->CameraLagSpeed = 12.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 60.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; FollowCamera->FieldOfView = 80.f;

	Progress = CreateDefaultSubobject<UHubProgress>(TEXT("Progress"));
}

void AHubCharacter::BeginPlay()
{
	Super::BeginPlay();
	ApplyRecipe(Progress->Recipe);
}

void AHubCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		EnsureInputAssets();
		if (UEnhancedInputLocalPlayerSubsystem* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Sub->ClearAllMappings();
			Sub->AddMappingContext(Mapping, 0);
		}
	}
}

void AHubCharacter::EnsureInputAssets()
{
	if (Mapping) return;
	auto MakeAction = [this](const TCHAR* Name, EInputActionValueType Type) { UInputAction* A = NewObject<UInputAction>(this, Name); A->ValueType = Type; return A; };
	if (!MoveAction) MoveAction = MakeAction(TEXT("IA_Move"), EInputActionValueType::Axis2D);
	if (!LookAction) LookAction = MakeAction(TEXT("IA_Look"), EInputActionValueType::Axis2D);
	if (!JumpAction) JumpAction = MakeAction(TEXT("IA_Jump"), EInputActionValueType::Boolean);
	if (!SprintAction) SprintAction = MakeAction(TEXT("IA_Sprint"), EInputActionValueType::Boolean);
	if (!InteractAction) InteractAction = MakeAction(TEXT("IA_Interact"), EInputActionValueType::Boolean);
	if (!ViewAction) ViewAction = MakeAction(TEXT("IA_View"), EInputActionValueType::Boolean);

	Mapping = NewObject<UInputMappingContext>(this, TEXT("IMC_Hub"));
	auto Swizzle = [this]() { return NewObject<UInputModifierSwizzleAxis>(this); };
	auto Negate = [this](bool X, bool Y, bool Z) { UInputModifierNegate* N = NewObject<UInputModifierNegate>(this); N->bX = X; N->bY = Y; N->bZ = Z; return N; };
	// move: W/S on Y, A/D on X
	Mapping->MapKey(MoveAction, EKeys::W).Modifiers.Add(Swizzle());
	{ FEnhancedActionKeyMapping& M = Mapping->MapKey(MoveAction, EKeys::S); M.Modifiers.Add(Swizzle()); M.Modifiers.Add(Negate(true, true, true)); }
	Mapping->MapKey(MoveAction, EKeys::D);
	Mapping->MapKey(MoveAction, EKeys::A).Modifiers.Add(Negate(true, true, true));
	Mapping->MapKey(MoveAction, EKeys::Gamepad_LeftX);
	Mapping->MapKey(MoveAction, EKeys::Gamepad_LeftY).Modifiers.Add(Swizzle());
	// look
	Mapping->MapKey(LookAction, EKeys::Mouse2D).Modifiers.Add(Negate(false, true, false));
	Mapping->MapKey(LookAction, EKeys::Gamepad_RightX);
	Mapping->MapKey(LookAction, EKeys::Gamepad_RightY).Modifiers.Add(Swizzle());
	Mapping->MapKey(JumpAction, EKeys::SpaceBar); Mapping->MapKey(JumpAction, EKeys::Gamepad_FaceButton_Bottom);
	Mapping->MapKey(SprintAction, EKeys::LeftShift); Mapping->MapKey(SprintAction, EKeys::Gamepad_LeftThumbstick);
	Mapping->MapKey(InteractAction, EKeys::E); Mapping->MapKey(InteractAction, EKeys::Gamepad_FaceButton_Left);
	Mapping->MapKey(ViewAction, EKeys::V); Mapping->MapKey(ViewAction, EKeys::Gamepad_RightThumbstick);
}

void AHubCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	EnsureInputAssets();
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHubCharacter::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHubCharacter::Look);
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AHubCharacter::DoJump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &AHubCharacter::StartSprint);
		EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHubCharacter::StopSprint);
		EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &AHubCharacter::Interact);
		EIC->BindAction(ViewAction, ETriggerEvent::Started, this, &AHubCharacter::CycleView);
	}
	else
	{
		UE_LOG(LogHub, Error, TEXT("Enhanced Input component missing: set DefaultPlayerInputClass/DefaultInputComponentClass in DefaultInput.ini"));
	}
}

void AHubCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (!Controller) return;
	const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
	AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::X), Axis.Y);
	AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y), Axis.X);
}

void AHubCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X); AddControllerPitchInput(Axis.Y);
}

void AHubCharacter::StartSprint(const FInputActionValue&) { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
void AHubCharacter::StopSprint(const FInputActionValue&) { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }

void AHubCharacter::DoJump(const FInputActionValue&)
{
	if (JumpCurrentCount >= 1 && !bTechWorks) { Toast(TEXT("No tech works here: the boost is dead")); return; }
	Jump();
}

void AHubCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	const float Drop = (FallStartZ - GetActorLocation().Z) / 100.f;   // metres
	if (Drop > 5.f && Progress) Progress->Hurt((Drop - 5.f) * 12.f, TEXT("fall"));
	bWasFalling = false;
}

void AHubCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const bool bFalling = GetCharacterMovement()->IsFalling();
	if (bFalling && !bWasFalling) FallStartZ = GetActorLocation().Z;
	if (bFalling) FallStartZ = FMath::Max(FallStartZ, GetActorLocation().Z);
	bWasFalling = bFalling;

	// nearest interactable within range decides the prompt
	InteractPrompt.Empty(); float Best = 1e9f;
	TArray<AActor*> Found; UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHubInteractable::StaticClass(), Found);
	for (AActor* A : Found)
	{
		AHubInteractable* I = Cast<AHubInteractable>(A); if (!I) continue;
		const float D = FVector::Dist(A->GetActorLocation(), GetActorLocation());
		if (D < I->UseRange && D < Best) { Best = D; InteractPrompt = I->Prompt; }
	}
}

void AHubCharacter::Interact(const FInputActionValue&)
{
	float Best = 1e9f; AHubInteractable* Target = nullptr;
	TArray<AActor*> Found; UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHubInteractable::StaticClass(), Found);
	for (AActor* A : Found)
	{
		AHubInteractable* I = Cast<AHubInteractable>(A); if (!I) continue;
		const float D = FVector::Dist(A->GetActorLocation(), GetActorLocation());
		if (D < I->UseRange && D < Best) { Best = D; Target = I; }
	}
	if (Target) Target->Interact(this);
}

void AHubCharacter::CycleView(const FInputActionValue&) { SetCameraView((CameraView + 1) % 3); }

void AHubCharacter::SetCameraView(int32 View)
{
	CameraView = View;
	static const float Lengths[3] = { 380.f, 180.f, 0.f };
	CameraBoom->TargetArmLength = Lengths[View];
	CameraBoom->SocketOffset = View == 2 ? FVector(0.f, 0.f, 70.f) : View == 1 ? FVector(0.f, 50.f, 55.f) : FVector(0.f, 0.f, 60.f);
	GetMesh()->SetOwnerNoSee(View == 2);
	Toast(View == 0 ? TEXT("Third person") : View == 1 ? TEXT("Shoulder") : TEXT("First person"));
}

void AHubCharacter::Toast(const FString& Message)
{
	LastToast = Message; LastToastTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
}

void AHubCharacter::DescribeAvatar(const FString& Words)
{
	if (!Progress) return;
	Progress->SetRecipeFromWords(Words);
	ApplyRecipe(Progress->Recipe);
	Toast(TEXT("Made: ") + UHubAvatarLibrary::DescribeRecipe(Progress->Recipe));
}
