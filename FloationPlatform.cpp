// Fill out your copyright notice in the Description page of Project Settings.


#include "FloationPlatform.h"

// Sets default values
AFloationPlatform::AFloationPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);
}

// Called when the game starts or when spawned
void AFloationPlatform::BeginPlay()
{
	Super::BeginPlay();
	FVector tempStartLocation = GetActorLocation();
	FVector StartLocation;
	if (bUseCustomStartPostion)
	{
		StartLocation = FVector(tempStartLocation.X, tempStartLocation.Y, FMath::Clamp(CustomStartPosition, MinZValue, MaxZValue));
	}
	else
	{
		StartLocation = FVector(tempStartLocation.X, tempStartLocation.Y, MinZValue);
	}
	
	SetActorLocation(StartLocation);
}

// Called every frame
void AFloationPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	float Difference = MaxZValue - MinZValue;
	float Current = Location.Z - MinZValue;
	float Ratio = Current / Difference;
	if (bGoingUp)
	{
		if (Location.Z < MaxZValue)
		{
			if (bUseFunction)
			{
				if (Ratio < 0.5f)
				{
					float UseRatio = Ratio;
					Location.Z += Increment * DeltaTime * FMath::Clamp(UseRatio, MinClamp, MaxClamp) * 10.f;
				}
				if (Ratio >= 0.5f)
				{
					float UseRatio = 1.f - Ratio;
					Location.Z += Increment * DeltaTime * FMath::Clamp(UseRatio, MinClamp, MaxClamp) * 10.f;
				}
				
			}
			else
			{
				Location.Z += Increment * DeltaTime;
			}
			
			SetActorLocation(Location);
		}
		else
		{
			Location.Z = MaxZValue;
			SetActorLocation(Location);
			bGoingUp = false;
		}
	}
	if (bGoingUp == false)
	{
		if (Location.Z > MinZValue)
		{
			if (bUseFunction)
			{
				if (Ratio < 0.5f)
				{
					float UseRatio = Ratio;
					Location.Z -= Increment * DeltaTime * FMath::Clamp(UseRatio, MinClamp, MaxClamp) * 10.f;
				}
				if (Ratio >= 0.5f)
				{
					float UseRatio = 1.f - Ratio;
					Location.Z -= Increment * DeltaTime * FMath::Clamp(UseRatio, MinClamp, MaxClamp) * 10.f;
				}

			}
			else
			{
				Location.Z -= Increment * DeltaTime;
			}
		
			SetActorLocation(Location);
		}
		else
		{
			Location.Z = MinZValue;
			SetActorLocation(Location);
			bGoingUp = true;
		}
	}
	FRotator Rotation = GetActorRotation();
	if (bUseCustomRotationIncrement)
	{
		Rotation.Yaw += CustomRotationIncrement * DeltaTime;
	}
	else
	{
		Rotation.Yaw += Increment * DeltaTime;
	}
	
	SetActorRotation(Rotation);
}

