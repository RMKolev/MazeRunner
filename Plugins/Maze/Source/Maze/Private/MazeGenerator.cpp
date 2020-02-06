// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::LogMazeScheme() const
{
	FString LoggingScheme;
	LoggingScheme.AppendChar('t');
	LoggingScheme.AppendChar('\n');
	for (auto MazeRow : MazeScheme)
	{
		for (auto MazeCell : MazeRow)
		{
			if (MazeCell != 0)
				LoggingScheme.AppendChar(MazeCell + 'a');
			else
				LoggingScheme.AppendChar(' ');
		}
		LoggingScheme.AppendChar('\n');
	}
	UE_LOG(Maze, Warning, TEXT("\n%s"), *LoggingScheme);
}

TArray<TArray<bool>> AMazeGenerator::GetWalkableTerrain() const
{
	TArray<TArray<bool>> Result;
	Result.SetNum(MazeScheme.Num());
	int8 WallCharacter = 0;
	if (CharacterMap.Contains(FName("Wall")))
	{
		WallCharacter = CharacterMap.FindChecked(FName("Wall"));
	}
	for (int i = 0; i < MazeScheme.Num(); ++i)
	{
		Result[i].SetNumZeroed(MazeScheme[i].Num());
	}
	for (int i = 0; i < MazeScheme.Num(); ++i)
	{
		for (int j = 0; j < MazeScheme.Num(); ++j)
		{
			if (MazeScheme[i][j] != 0 && MazeScheme[i][j] != WallCharacter)
			{
				Result[i][j] = true;
			}
		}
	}
	return Result;
}

TArray<TArray<int8>> AMazeGenerator::GetMazeScheme() const
{
	return this->MazeScheme;
}

void AMazeGenerator::SetSeed(int32 Seed)
{
	this->WorldSeed = Seed;
	this->RStream.Initialize(Seed);
}

void AMazeGenerator::SetCharacterMap(const TMap<int8, FMazeProperties>& Map )
{
	for (auto MapItem : Map)
	{
		if (this->CharacterMap.Contains(MapItem.Value.ComponentName))
		{
			UE_LOG(Maze, Error, TEXT("MazeRoomGenerator:SetCharacterMap - There is already a component with the same name in the map! (%s)")
				   , *MapItem.Value.ComponentName.ToString());
		}
		else
		{
			this->CharacterMap.Add(MapItem.Value.ComponentName, MapItem.Value.Id);
		}
	}
}

