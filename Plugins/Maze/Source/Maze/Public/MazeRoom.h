// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeActor.h"
#include "Rectangle.h"
#include "MazeRoom.generated.h"

UCLASS()
class MAZE_API AMazeRoom : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = MapsAndSets, EditAnywhere)
		TMap<FMazePoint, AMazeActor*> components;
	UPROPERTY(EditAnywhere)
		FMazePoint coordinates; // Position of the room in the maze. Uses global coordinate system

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AMazeRoom();
	auto GetComponentIterator() const;
};
