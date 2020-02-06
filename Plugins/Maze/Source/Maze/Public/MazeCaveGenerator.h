// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeGenerator.h"
#include "MazeCaveGenerator.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeCaveGenerator : public AMazeGenerator
{
	GENERATED_BODY()

public:
	virtual void BuildMaze() override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 Height;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 Width;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 FillPercentige;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 NumberOfIterations;

	TArray<TArray<int8>> PrevCaveIteration;

	void TransferCave();
	void RandomFill();
	int32 GetNeighbourWallCount(int32 CurrI, int32 CurrJ) const;
	void SmoothingIteration();
};
