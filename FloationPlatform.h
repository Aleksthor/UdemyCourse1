// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloationPlatform.generated.h"

UCLASS()
class UDEMYCOURSEPART1_API AFloationPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloationPlatform();

	/** This is the mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Platform)
	UStaticMeshComponent* PlatformMesh;

	/** This is the value where our floater will start to move upwards and downwards
	**  between these values
	**  The Min value is also in BeginPlay() to not crash the game
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	float MinZValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	float MaxZValue = 1000.f;

	/** If we want to use a custom stating position (Default is MinZValue)
	**	We also Clamp this CustomPosistion to not crash the game
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	bool bUseCustomStartPostion = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	float CustomStartPosition = 0.f;

	
	/** Function is a tool we can use to have different speeds in the middle and near poles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	bool bUseFunction = false;
	/** Min Clamp needs to be above 0.f, if it reaches 0, the funcitons stops at the first pole hit 
	**  Max Clamp can only be between MinClamp and 0.5f, higher values wouldnt change anything
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	float MinClamp = 0.07f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
	float MaxClamp = 0.25f;

	/** Custom Rotation can be set. Default is the same value as Up/Down uses 
	**  Need bUseCustomRotation to be set to true in blueprints
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rotation)
	float CustomRotationIncrement = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rotation)
		bool bUseCustomRotationIncrement = false;
	
	/** Default Increment Vaule*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown)
		float Increment = 5.f; // also times DeltaTime to get a uniform speed on all clients

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool bGoingUp = true;
	float CurrentTime;
	
	
};
