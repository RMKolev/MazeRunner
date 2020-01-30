// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBuilder.h"
#include "Maze.h"
#include "MazeActor.h"
#include "Engine/World.h"

// Sets default values
ABlockBuilder::ABlockBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	XPosition = 0.f;
	CurrTime = 0.f;
	PrevPosition.X = 0;
	PrevPosition.Y = 0;
	PrevPosition.Z = 0;
	UE_LOG(Maze, Error, TEXT("ABlockBuilder::ABlockBuilder() Can i haz log?"));

}

// Called when the game starts or when spawned
void ABlockBuilder::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(Maze, Error, TEXT("ABlockBuilder::ABlockBuilder() IsValid(World) == false"));
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	char maze[][50] = { "####################",
						"ffffffff###fffffff##",
						"fffffffffffffffffff#",
						"###ffffffffffffffff#",
						"####################" };
	
	int rows = 5;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; maze[i][j] != '\0'; j++)
		{
			FVector SpawnLocation = GetActorLocation() + FVector(i * 100.f, j * 100.f, 0);
			if (maze[i][j] == '#')
			{
				SpawnLocation.Z += 100.f;
				AActor* Wall = World->SpawnActor<AActor>(WallActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				/*FVector WallScale = Wall->GetActorScale();
				Wall->SetActorLocation(FVector(WallScale.X * i, WallScale.Y * j, WallScale.Z));*/
			} else if (maze[i][j] == 'f'){
				
				AActor * Floor = World->SpawnActor<AActor>(FloorActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				/*FVector Scale = Floor->GetActorScale();
				Floor->SetActorLocation(FVector(Scale.X * i, Scale.Y * j, 0));*/
			}
		}
	}
	
}

// Called every frame
void ABlockBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*CurrTime += DeltaTime;

	if (CurrTime >= 1.f)
	{
		CurrTime = 0.f;

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		FVector SpawnLocation = PrevPosition + FVector(100.f, 0, 0);

		UWorld* World = GetWorld();
		if (IsValid(World) == false)
		{
			UE_LOG(Maze, Error, TEXT("ABlockBuilder::ABlockBuilder() IsValid(World) == false"));
		}
		AMazeActor* Wall = World->SpawnActor<AMazeActor>(WallActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);

		PrevPosition = SpawnLocation;
	}*/
}

