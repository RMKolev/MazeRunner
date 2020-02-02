// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rectangle.h"
#include "MazeActor.h"
#include "MazeBasis.generated.h"


UCLASS()
class MAZE_API AMazeBasis : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FVector start; //The position of 0,0 
	UPROPERTY(EditAnywhere)
		FVector scale;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AMazeBasis(FVector, FVector);
	AMazeBasis();
	FVector GetMazePointLocation(FMazePoint) const;
	FVector GetMazeActorLocation(FMazePoint,const AMazeActor&) const;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};