// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBuilder.h"
#include "Maze.h"
#include "Engine/World.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CaveGeneration.h"

// Sets default values
ABlockBuilder::ABlockBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Anchor point"));
	WallInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Wall Instanced Mesh"));
	WallInstancedMesh->SetAbsolute(false, false, false);
	FloorInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor Instanced Mesh"));
	FloorInstancedMesh->SetAbsolute(false, false, false);

	WallInstancedMesh->SetRelativeLocation(FVector(0, 0, 0));
	FloorInstancedMesh->SetRelativeLocation(FVector(0, 0, -SideOfCubeAtScaleOne * ScaleForAllMeshes.Z));
}

// Called when the game starts or when spawned
void ABlockBuilder::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(Maze, Error, TEXT("ABlockBuilder::ABlockBuilder() Can i haz log?"));

	//UWorld* World = GetWorld();
	//if (IsValid(World) == false)
	//{
	//	UE_LOG(Maze, Error, TEXT("ABlockBuilder::ABlockBuilder() IsValid(World) == false"));
	//}

	/*FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;*/

	WallInstancedMesh->SetRelativeLocation(FVector(0, 0, 0));
	FloorInstancedMesh->SetRelativeLocation(FVector(0, 0, -SideOfCubeAtScaleOne * ScaleForAllMeshes.Z));

	const int rows = 20;
	const int cols = 20;

	FCaveGeneration CaveGen(0, rows, cols, 45, 5);
	CaveGen.GenerateCave();
	
	TArray<TArray<char>> maze;
	CaveGen.ToAMazeRoom(maze);

	//if (!IsValid(WallActorClass))
	//{
	//	UE_LOG(Maze, Error, TEXT("ABlockBuilder::BeginPlay() WallActorClass is not Valid!"));
	//}
	//UStaticMeshComponent* WallMesh = (UStaticMeshComponent*)WallActorClass->GetDefaultObject<AMazeActor>()->FindComponentByClass(UStaticMeshComponent::StaticClass());
	//if(IsValid(WallMesh))
	//{
	//	UE_LOG(Maze, Error, TEXT("ABlockBuilder::BeginPlay() WallMesh is Valid!"));
	//	WallInstancedMesh->SetStaticMesh(WallMesh->GetStaticMesh());
	//}
	//else 
	//{
	//	WallInstancedMesh->SetStaticMesh(DefaultMesh->GetStaticMesh());
	//}
	
	

	//if (!IsValid(FloorActorClass))
	//{
	//	UE_LOG(Maze, Error, TEXT("ABlockBuilder::BeginPlay() FloorActorClass is not Valid!"));
	//}
	//UStaticMeshComponent* FloorMesh = (UStaticMeshComponent*)FloorActorClass->GetDefaultObject<AMazeActor>()->FindComponentByClass(UStaticMeshComponent::StaticClass());
	//if (IsValid(FloorMesh))
	//{
	//	UE_LOG(Maze, Error, TEXT("ABlockBuilder::BeginPlay() FloorMesh is Valid!"));
	//	FloorInstancedMesh->SetStaticMesh(FloorMesh->GetStaticMesh());
	//}
	//else
	//{
	//	FloorInstancedMesh->SetStaticMesh(DefaultMesh->GetStaticMesh());
	//}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			FVector SpawnLocation = /*GetActorLocation() +*/ FVector(i * SideOfCubeAtScaleOne * ScaleForAllMeshes.X, 
																j * SideOfCubeAtScaleOne * ScaleForAllMeshes.Y, 0);
			if (maze[i][j] == '#')
			{
				//SpawnLocation.Z = SideOfCubeAtScaleOne * ScaleForAllMeshes.Z;
				FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
				//AActor* Wall = World->SpawnActor<AActor>(WallActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				//Wall->SetActorScale3D(ScaleForAllMeshes);
				WallInstancedMesh->AddInstance(SpawnTransform);
				FloorInstancedMesh->AddInstance(SpawnTransform);
			
			} else if (maze[i][j] == '_') {
				FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
				/*AActor * Floor = World->SpawnActor<AActor>(FloorActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				Floor->SetActorScale3D(ScaleForAllMeshes);*/
				FloorInstancedMesh->AddInstance(SpawnTransform);
			}
		}
	}
	
}

// Called every frame
void ABlockBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

