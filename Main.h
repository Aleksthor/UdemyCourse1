// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Main.generated.h"

UCLASS()
class UDEMYCOURSEPART1_API AMain : public ACharacter
{
	GENERATED_BODY()
	


public:
	// Sets default values for this character's properties
	AMain();


	/** SpringArm used to help with camera collission */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAvvess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera that follows the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAvvess = "true"))
	class UCameraComponent* PlayerCamera;

	/** Base turn rate to scare turning functions for the Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	float BaseTurnRate;

	/** Base look up rate to scare turning functions for the Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forward/backwards input */
	void MoveForward(float Value);

	/** Called for Right/Left input */
	void MoveRight(float Value);

	/** 
	Called via input to (turn at / look up) a given rate 
	Rate - Normalized rate i.e 1.0f means 100% of desired (turn rate / look up rate)
	*/
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return PlayerCamera; }

};
