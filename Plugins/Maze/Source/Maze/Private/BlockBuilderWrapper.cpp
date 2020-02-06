// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBuilderWrapper.h"
#include "Maze.h"

// Sets default values
ABlockBuilderWrapper::ABlockBuilderWrapper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ABlockBuilder* ABlockBuilderWrapper::SpawnBlockBuilderBP(FVector Location, FRotator Rotation, FActorSpawnParameters SpawnInfo)
{

	if (BlockBuilderClass != NULL)
	{
		ABlockBuilder* CavebasedMaze = GetWorld()->SpawnActor<ABlockBuilder>(BlockBuilderClass, Location, Rotation, SpawnInfo);

		FString MazeName("Cavebased Maze");

		CavebasedMaze->Rename(*MazeName);
		CavebasedMaze->SetActorLabel(*MazeName);

		UE_LOG(Maze, Warning, TEXT("New cavebased maze."));

		return CavebasedMaze;
	}

	UE_LOG(Maze, Warning, TEXT("Cannot generate maze, there is no BP class specified."));

	return nullptr;
}


// Called when the game starts or when spawned
void ABlockBuilderWrapper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBuilderWrapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

