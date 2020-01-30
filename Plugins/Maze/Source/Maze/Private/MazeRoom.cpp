// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeRoom.h"

// Sets default values
AMazeRoom::AMazeRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

auto AMazeRoom::GetComponentIterator() const
{
	return components.CreateConstIterator();
}

// Called when the game starts or when spawned
void AMazeRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

