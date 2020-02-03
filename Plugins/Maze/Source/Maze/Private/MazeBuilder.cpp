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
	this->world = GetWorld();
	if (!IsValid(world)) {
		UE_LOG(Maze, Error, TEXT("AMazeBuilder::BeginPlay() world == nullptr"));
	}

	for (auto instance : assets) {
		auto val = NewObject<UInstancedStaticMeshComponent>(this, instance.Value);
		val->RegisterComponent();
		instanceMeshes.Add(instance.Key, val);
	}
}

// Called every frame
void AMazeBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

