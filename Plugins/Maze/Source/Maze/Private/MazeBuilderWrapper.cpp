// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBuilderWrapper.h"
#include "MazeBuilder.h"
#include "Maze.h"

// Sets default values
AMazeBuilderWrapper::AMazeBuilderWrapper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMazeBuilderWrapper::InstantiateMazeBuilder()
{
	FVector Location = FVector(0.0f);
	FRotator Rotation = FRotator(0, 0, 0);

	AMazeBuilder* MBInstance = (AMazeBuilder*)GetWorld()->SpawnActor(MazeBuilderClass, &Location, &Rotation);

	if (MBInstance->bGenerateOnPlay == false)
	{
		MBInstance->GenerateMaze();
	}
	if (MBInstance->bBuildOnPlay == false)
	{
		MBInstance->RegisterInstanceMeshComponents();
		MBInstance->RegisterAllComponents();
		MBInstance->BuildMaze();
	}

	UE_LOG(Maze, Log, TEXT("A maze builder instantiated."));

	/*

	if (MazeBuilderClass != NULL)
	{
		AMazeBuilder* CavebasedMaze = GetWorld()->SpawnActor<ABlockBuilder>(MazeBuilderClass, Location, Rotation, SpawnInfo);

		FString MazeName("Cavebased Maze");

		CavebasedMaze->Rename(*MazeName);
		CavebasedMaze->SetActorLabel(*MazeName);

		return CavebasedMaze;
	}

	UE_LOG(Maze, Warning, TEXT("Cannot generate maze, there is no BP class specified."));

	return nullptr;

			*/
}


// Called when the game starts or when spawned
void AMazeBuilderWrapper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeBuilderWrapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

