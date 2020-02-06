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
	FVector ScaleForAllMeshes = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(Category = MazeAlgorithm, EditAnywhere)
	TSubclassOf<class AMazeGenerator> MG;

public:
	void BuildMaze() override;
	void BeginPlay() override;
	void BuildMazeFromScheme(const TArray<TArray<int8>>& MazeScheme);
};
