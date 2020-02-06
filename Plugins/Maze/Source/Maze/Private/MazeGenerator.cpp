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

TArray<TArray<int8>> AMazeGenerator::GetMazeScheme() const
{
	return this->MazeScheme;
}

void AMazeGenerator::SetSeed(int32 Seed)
{
	this->WorldSeed = Seed;
	this->RStream.Initialize(Seed);
}

