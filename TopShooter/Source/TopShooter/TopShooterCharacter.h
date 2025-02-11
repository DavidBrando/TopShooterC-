// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopShooterCharacter.generated.h"

class AWeapons;


UCLASS(Blueprintable)
class ATopShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopShooterCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay();
	void MoveForward(float axis);
	void MoveRight(float axis);
	void SettingMovement(bool yawControl, bool orientationMotion);

	void ShootWeapon();

	void ReleaseWeapon();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	AWeapons* GetCurrentWeapon() { return currentWeapon; }

	bool GetAlive();
	void LookAtPosition(FVector pos);

	void HealSystem(float f);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	bool dying;
	

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapons> myWeapon;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = InfoCharacter, meta = (AllowPrivateAccess = "true"))
	AWeapons *currentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = InfoCharacter, meta = (AllowPrivateAccess = "true"))
	class UHealhSystemComponent* healthSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InfoCharacter, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage;

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;


};

