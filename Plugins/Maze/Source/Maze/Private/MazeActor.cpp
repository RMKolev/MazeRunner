// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeActor.h"
#include "MazeBasis.h" // Temp for testing
// Sets default values
AMazeActor::AMazeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMazeActor::UpdateScale(const FIntVector& newScale)
{
	if (newScale.X > 0 && newScale.Y > 0 && newScale.Z) {
		this->currentMazeScale = newScale;
	}
}

// Called when the game starts or when spawned
void AMazeActor::BeginPlay()
{
	Super::BeginPlay();
}

FIntVector AMazeActor::GetCurrentScale() const
{
	return currentMazeScale;
}

// Called every frame
void AMazeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

