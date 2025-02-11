// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TopShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/Material.h"
#include "Weapons.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "HealhSystemComponent.h"


ATopShooterCharacter::ATopShooterCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}

	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	healthSystem = CreateDefaultSubobject<UHealhSystemComponent>(TEXT("InfoPlayer"));
	this->AddOwnedComponent(healthSystem);

	dying = false;

}

void ATopShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	currentWeapon = GetWorld()->SpawnActor<AWeapons>(myWeapon,FVector(0.0f), FRotator(0.0f), SpawnParams);

	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	currentWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()), rules, "WeaponSocket");
	healthSystem->SettingHeal(125.0f);

}

void ATopShooterCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}




void ATopShooterCharacter::MoveForward(float axis) {

	if ((Controller != NULL) && (axis != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, axis);
	}

}

void ATopShooterCharacter::MoveRight(float axis) {

	if ((Controller != NULL) && (axis != 0.0f))
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, axis);
	}

}

bool ATopShooterCharacter::GetAlive()
{
	return healthSystem->GetAlive();
}

void ATopShooterCharacter::LookAtPosition(FVector pos)
{

	const FVector myPos = GetActorLocation();
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(myPos, pos);

	SetActorRotation(FRotator(0.0f, rot.Yaw, 0.0f));
}


void ATopShooterCharacter::HealSystem(float f)
{
	healthSystem->Heal(f);
}

float ATopShooterCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	bool alive = healthSystem->TakeDamage(Damage);

	if (alive == false) {


		if (AnimMontage && dying == false) {

			dying = true;

			float time = PlayAnimMontage(AnimMontage);

		}

		else {
			Destroy();
		}
	}

	return Damage;
}

void ATopShooterCharacter::SettingMovement(bool yawControl, bool orientationMotion)
{
	bUseControllerRotationYaw = yawControl;
	GetCharacterMovement()->bOrientRotationToMovement = orientationMotion;
}


void ATopShooterCharacter::ShootWeapon() {

	currentWeapon->SetAutoFire(true);
	currentWeapon->ShootProjectile();

}

void ATopShooterCharacter::ReleaseWeapon() {
	currentWeapon->SetAutoFire(false);

}
