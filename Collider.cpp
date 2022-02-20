// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyPawnMovementComponent.h"

// Sets default values
ACollider::ACollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SetRootComponent(SphereComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(40.f);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	MeshComponent->SetStaticMesh(StaticMeshFinder.Object);
	MeshComponent->SetupAttachment(SphereComponent);
	MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	MeshComponent->SetWorldScale3D(FVector(0.8, 0.8, 0.8));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(SphereComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 400.f;

	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 3.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	

	MyPawnMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MyPawnMovementComponent"));
	MyPawnMovementComponent->UpdatedComponent = RootComponent;

	CameraInput = FVector2D(0.f, 0.f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	FRotator NewSpringArmRotation = SpringArmComponent->GetComponentRotation();
	//NewSpringArmRotation.Pitch += FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, (-80.f), (-15.f)); // Ensure that SpringArmRotation will never get below -80.f and never above -15.f
	NewSpringArmRotation.Pitch += CameraInput.Y;
	if (NewSpringArmRotation.Pitch > -80.f && NewSpringArmRotation.Pitch < -10.f)
	{
		SpringArmComponent->SetWorldRotation(NewSpringArmRotation);
	}
	
}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::YawCamera);
}

void ACollider::MoveForward(float input)
{
	FVector Forward = GetActorForwardVector();

	if (MyPawnMovementComponent)
	{
		MyPawnMovementComponent->AddInputVector(Forward * input);
	}
}

void ACollider::MoveRight(float input)
{
	FVector Right = GetActorRightVector();

	if (MyPawnMovementComponent)
	{
		MyPawnMovementComponent->AddInputVector(Right * input);
	}
}

void ACollider::YawCamera(float input)
{
	CameraInput.X = input;
}

void ACollider::PitchCamera(float input)
{
	CameraInput.Y = input;
}


UPawnMovementComponent* ACollider::GetMovementComponent() const
{
	return MyPawnMovementComponent;
}


