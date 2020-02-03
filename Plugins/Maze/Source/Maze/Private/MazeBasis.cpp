// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBasis.h"

AMazeBasis::AMazeBasis(FVector start, FVector scale) : start(start)
{
	if (scale.X > 0 && scale.Y > 0 && scale.Z > 0) this->scale = scale;
}

// Sets default values
AMazeBasis::AMazeBasis() : start(FVector(0,0,0)), scale(FVector(1,1,1))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

FVector AMazeBasis::GetMazePointLocation(FIntPoint mp) const
{
	return start + FVector(mp.X + 0.5, mp.Y  + 0.5,0) * scale;
}

FVector AMazeBasis::GetMazeActorLocation(FIntPoint mp, const AMazeActor& ma) const
{
	FIntVector actorScale = ma.GetCurrentScale();
	return GetMazePointLocation(mp)+FVector(actorScale.X-1, actorScale.Y-1,actorScale.Z-1)*(scale/2);
}

// Called when the game starts or when spawned
void AMazeBasis::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMazeBasis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

