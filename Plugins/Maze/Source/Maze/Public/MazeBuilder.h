// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeRoom.h"
#include "MazeActor.h"
#include "MazeBuilder.generated.h"

USTRUCT()
struct FMazeBasic {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FVector start; //The position of 0,0 
	UPROPERTY(EditAnywhere)
		FVector scale;

	FMazeBasic(FVector start, FVector scale) : start(start)
	{
		if (scale.X > 0 && scale.Y > 0 && scale.Z > 0) this->scale = scale;
	}
	FMazeBasic() :FMazeBasic(FVector(0, 0, 0), FVector(100, 100, 100)) {};
	FVector GetMazePointLocation(FMazePoint mp) const
	{
		return start + FVector(mp.x + 0.5, mp.y + 0.5, 0) * scale;
	}
	FVector GetMazeActorLocation(FMazePoint mp, const AMazeActor& ma) const
	{
		FIntVector actorScale = ma.GetCurrentScale();
		return GetMazePointLocation(mp) + FVector(actorScale.X - 1, actorScale.Y - 1, actorScale.Z - 1) * (scale / 2);
	}
	FVector GetMazeActorLocation(FMazePoint mp, const FIntVector actorScale) const
	{
		return GetMazePointLocation(mp) + FVector(actorScale.X - 1, actorScale.Y - 1, actorScale.Z - 1) * (scale / 2);
	}
};

UCLASS()
class MAZE_API AMazeBuilder : public AActor
{
	GENERATED_BODY()
	
protected:	
	UWorld* world;
	UPROPERTY(EditAnywhere)
	TMap<FString,TSubclassOf<AMazeActor>> assets;
	UPROPERTY(EditAnywhere)
	FMazeBasic basis;
	virtual void BeginPlay() override;
public:	
	// Function to build the maze. To be implemented in heirs of class.
	virtual void BuildMaze() {};
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AMazeBuilder();
};
