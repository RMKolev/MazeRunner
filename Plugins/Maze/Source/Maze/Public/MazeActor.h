// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeActor.generated.h"

UCLASS()
class MAZE_API AMazeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(EditAnywhere)
	FIntVector originalMazeScale; //Original Maze scaling, how much  1x1 squares of the maze it takes
	
	UPROPERTY(EditAnywhere)
	FIntVector currentMazeScale; //Current scaling, how much 1x1 squares of the maze it takes

	UPROPERTY(EditAnywhere)
	bool bCanContainAssets = false;

	UPROPERTY(EditAnywhere)
	bool bScalable = false;

	virtual bool CanBePlaced() { return true; };
	// Sets default values for this actor's properties
	AMazeActor();
	// Will Scale the actor from top left corner of his bounding box.
	void UpdateScale(const FIntVector&);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
