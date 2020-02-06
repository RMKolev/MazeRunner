// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeBlockBuilder.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeBlockBuilder : public AMazeBuilder
{
	GENERATED_BODY()
	
private:
	float SideOfCubeAtScaleOne = 100.f;

	UPROPERTY(EditDefaultsOnly)
	int32 Seed; // Sets what seed the random number generator should use. If equal to 0, then a new seed will be generated.

	UPROPERTY(EditDefaultsOnly)
	int32 Height = 20;

	UPROPERTY(EditDefaultsOnly)
	int32 Width = 20;

	UPROPERTY(EditDefaultsOnly)
	int32 FillPercentige;

	UPROPERTY(EditDefaultsOnly)
	int32 NumberOfIterations = 5;

	UPROPERTY(EditDefaultsOnly)
	FVector ScaleForAllMeshes = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY()
	class UInstancedStaticMeshComponent* WallInstancedMesh;

	UPROPERTY(EditDefaultsOnly)
	class UInstancedStaticMeshComponent* FloorInstancedMesh;

public:
	UFUNCTION()
	void BuildMaze() override;
};
