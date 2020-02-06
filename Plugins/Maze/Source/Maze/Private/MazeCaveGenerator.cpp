// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCaveGenerator.h"
#include "Maze.h"

void AMazeCaveGenerator::BeginPlay()
{
	if (bUseCustomSeed)
	{
		SetSeed(WorldSeed);
	}
	else
	{
		RStream.GenerateNewSeed();
	}

	BuildMaze();
}

void AMazeCaveGenerator::TransferCave()
{
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			PrevCaveIteration[i][j] = MazeScheme[i][j];
		}
	}
}

void AMazeCaveGenerator::RandomFill()
{
	if (!CharacterMap.Contains(FName("Floor")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room Floors"));
		return;
	}
	int8 FloorCharacter = CharacterMap.FindChecked(FName("Floor"));
	if (!CharacterMap.Contains(FName("Wall")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room walls"));
		return;
	}
	int8 WallCharacter = CharacterMap.FindChecked(FName("Wall"));

	UE_LOG(Maze, Warning, TEXT("Floor Character: %d  Wall Character: %d"), FloorCharacter, WallCharacter);
	for (int32 i = 0; i < Height; ++i)
	{
		MazeScheme[i][0] = WallCharacter;
		MazeScheme[i][Width - 1] = WallCharacter;
	}
	for (int32 j = 0; j < Width; ++j)
	{
		MazeScheme[0][j] = WallCharacter;
		MazeScheme[Height - 1][j] = WallCharacter;
	}
	for (int32 i = 1; i < Height - 1; ++i)
	{
		for (int32 j = 1; j < Width - 1; ++j)
		{
			MazeScheme[i][j] = RStream.RandRange(0, 100) > FillPercentige ? FloorCharacter : WallCharacter;
		}
	}
}

int32 AMazeCaveGenerator::GetNeighbourWallCount(int32 CurrI, int32 CurrJ) const
{
	if (!CharacterMap.Contains(FName("Wall")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room walls"));
		return -1;
	}
	int8 WallCharacter = CharacterMap.FindChecked(FName("Wall"));

	int32 WallCount = 0;
	for (int32 i = CurrI - 1; i <= CurrI + 1; ++i)
	{
		for (int32 j = CurrJ - 1; j <= CurrJ + 1; ++j)
		{
			if (i > 0 && i < Height && j > 0 && j < Width)
			{
				if (i != CurrI || j != CurrJ)
				{
					WallCount = WallCount + (PrevCaveIteration[i][j] == WallCharacter);
				}
			}
			else ++WallCount;
		}
	}

	return WallCount;
}

void AMazeCaveGenerator::SmoothingIteration()
{
	if (!CharacterMap.Contains(FName("Floor")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room Floors"));
		return;
	}
	int8 FloorCharacter = CharacterMap.FindChecked(FName("Floor"));
	if (!CharacterMap.Contains(FName("Wall")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room walls"));
		return;
	}
	int8 WallCharacter = CharacterMap.FindChecked(FName("Wall"));

	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			int32 WallCount = GetNeighbourWallCount(i, j);
			if (WallCount > 4) MazeScheme[i][j] = WallCharacter;
			if (WallCount < 4) MazeScheme[i][j] = FloorCharacter;
		}
	}
}

void AMazeCaveGenerator::BuildMaze()
{
	MazeScheme.SetNum(Height);
	PrevCaveIteration.SetNum(Height);
	for (int32 i = 0; i < Height; ++i)
	{
		MazeScheme[i].SetNum(Width);
		PrevCaveIteration[i].SetNum(Width);
	}

	RandomFill();
	LogMazeScheme();
	for (int32 i = 0; i < NumberOfIterations; ++i)
	{
		TransferCave();
		SmoothingIteration();
		UE_LOG(Maze, Error, TEXT("iteration %d"), i);
		LogMazeScheme();
	}
}
