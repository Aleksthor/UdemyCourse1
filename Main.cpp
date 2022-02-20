// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Adjust the Capsule Size ( This is the Root Component )
	GetCapsuleComponent()->SetCapsuleSize(50.f, 105.f);

	// Create Spring Arm and attach it to the Root(CapsuleComponent)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f; // Distance from player
	SpringArm->bUsePawnControlRotation = true; // Rotate arm based on controller
	SpringArm->IsUsingAbsoluteRotation();	
	
	
	

	// Create the Camera and attach it to the SpringArm
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// Let the SpringArm handle Controller Orientation
	PlayerCamera->bUsePawnControlRotation = false;
	
	// Set our turn rates for input
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// Allows the Character to stand still and face same direction 
	// Do not rotate when Controller does
	// That only affects the Camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;


	// Configure Character Movement.
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character Moves in the Direction of Input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 700.f, 0.f); // ... at this rotation rate / Smooth transitions between directions
	GetCharacterMovement()->JumpZVelocity = 700.f; // Jump Velocity
	GetCharacterMovement()->AirControl = 0.5f;

	
	
	
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// Jump with SpaceBar
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Moving with WASD
	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);

	// Turn Camera with arrows
	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpAtRate);

	// Turn Camera with mouse
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


}


void AMain::MoveForward(float Value)
{
	// Ensures no crashing checking if its not a nullptr
	if ((Controller != nullptr) && (Value != 0.f))
	{
		// Find out what way is forward
		// Getting the Vector of the Controller. This is our SpringArm
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // Canceling out X and Z Rotation.

		// Here we are basically getting the local X vector with a unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	

}


void AMain::MoveRight(float Value)
{
	// Ensures no crashing checking if its not a nullptr
	if ((Controller != nullptr) && (Value != 0.f))
	{
		// Find out what way is forward
		// Getting the Vector of the Controller. This is our SpringArm
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // Canceling out X and Z Rotation.

		// Here we are basically getting the local Y vector with a unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
void AMain::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void AMain::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
