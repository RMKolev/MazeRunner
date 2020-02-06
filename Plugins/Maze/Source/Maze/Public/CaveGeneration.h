// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAZE_API FCaveGeneration
{
private:
	int32 Seed;
	int32 Height;
	int32 Width;
	int32 FillPercentige;
	int32 NumberOfIterations;

	//UPROPERTY()
	TArray<TArray<char>> Cave;
	TArray<TArray<char>> PrevCaveIteration;

	struct FRandomStream RNG;

	void TransferCave();
public:
	FCaveGeneration();
	FCaveGeneration(int32 Seed, int32 Height, int32 Width, int32 FillPercentige, int32 NumberOfIterations) :
		Seed(Seed), Height(Height), Width(Width), FillPercentige(FillPercentige), NumberOfIterations(NumberOfIterations)
	{
		if (Seed == 0)
		{
			RNG.GenerateNewSeed();
		} 
		else
		{
			RNG.Initialize(Seed);
		}

		Cave.SetNum(Height);
		PrevCaveIteration.SetNum(Height);
		for (int32 i = 0; i < Height; ++i)
		{
			Cave[i].SetNum(Width);
			PrevCaveIteration[i].SetNum(Width);
		}
	}
	~FCaveGeneration();

	void RandomFill();
	int32 GetNeighbourWallCount(int32 CurrI, int32 CurrJ) const;
	void SmoothingIteration();
	void GenerateCave();
	void ToAMazeRoom(TArray<TArray<char>>& Target) const;
};
