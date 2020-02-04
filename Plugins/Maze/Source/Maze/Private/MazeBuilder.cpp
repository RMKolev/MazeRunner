// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBuilder.h"
#include "Engine/World.h"
#include "Maze.h"

// Sets default values
AMazeBuilder::AMazeBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeBuilder::BeginPlay()
{
	Super::BeginPlay();
	this->World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(Maze, Error, TEXT("AMazeBuilder::BeginPlay() World == nullptr"));
	}

	for (auto Instance : Assets) {
		auto Val = NewObject<UInstancedStaticMeshComponent>(this, Instance.Value);
		Val->RegisterComponent();
		InstanceMeshes.Add(Instance.Key, Val);
	}
}

// Called every frame
void AMazeBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeBuilder::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	this->InstanceMeshes.Empty();
	Super::EndPlay(EndPlayReason);
}

