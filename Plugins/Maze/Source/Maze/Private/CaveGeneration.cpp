// Fill out your copyright notice in the Description page of Project Settings.


#include "CaveGeneration.h"
#include "Math/RandomStream.h"

void FCaveGeneration::TransferCave()
{
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			PrevCaveIteration[i][j] = Cave[i][j];
		}
	}
}

FCaveGeneration::FCaveGeneration()
{
}

FCaveGeneration::~FCaveGeneration()
{
}

void FCaveGeneration::RandomFill()
{
	for (int32 i = 0; i < Height; ++i)
	{
		Cave[i][0] = '#';
		Cave[i][Width - 1] = '#';
	}
	for (int32 j = 0; j < Width; ++j)
	{
		Cave[0][j] = '#';
		Cave[Height - 1][j] = '#';
	}
	for (int32 i = 1; i < Height - 1; ++i)
	{
		for (int32 j = 1; j < Width - 1; ++j)
		{
			Cave[i][j] = RNG.RandRange(0, 100) > FillPercentige ? '_' : '#';
		}
	}
}

int32 FCaveGeneration::GetNeighbourWallCount(int32 CurrI, int32 CurrJ) const
{
	int32 WallCount = 0;

	for (int32 i = CurrI - 1; i < CurrI + 2; ++i)
	{
		for (int32 j = CurrJ - 1; j < CurrJ + 2; ++j)
		{
			if (i > 0 && i < Height && j > 0 && j < Width)
			{
				if (i != CurrI || j != CurrJ)
					WallCount = WallCount + (PrevCaveIteration[i][j] == '#');
			}
			else ++WallCount;
		}
	}

	return WallCount;
}

void FCaveGeneration::SmoothingIteration()
{
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			int32 WallCount = GetNeighbourWallCount(i, j);
			if (WallCount > 4) Cave[i][j] = '#';
			if (WallCount < 4) Cave[i][j] = '_';
		}
	}
}

void FCaveGeneration::GenerateCave()
{
	RandomFill();

	for (int32 i = 0; i < NumberOfIterations; ++i)
	{
		TransferCave();
		SmoothingIteration();
	}
}

void FCaveGeneration::ToAMazeRoom(TArray<TArray<char>>& Target) const
{
	Target.Empty();
	Target.Append(Cave);
	/*Target.SetNum(Height);
	for (int32 i = 0; i < Height; ++i)
	{
		Target[i].SetNum()
	}*/
}
