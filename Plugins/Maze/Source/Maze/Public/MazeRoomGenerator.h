// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rectangle.h"
#include "GameFramework/Actor.h"
#include "Maze.h"
#include "MazeGenerator.h"
#include "MazeRoomGenerator.generated.h"

UCLASS()
class MAZE_API AMazeRoomGenerator : public AMazeGenerator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMazeRoomGenerator();
	virtual void BuildMaze() override;
	virtual void LogMazeScheme() const override;

	virtual TArray<TArray<int8>> GetMazeScheme() const override;

	virtual FIntPoint GetRandomCharacterStartingPoint() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 NumberOfRooms;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint MinimalRoomScale;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint MaximumRoomScale;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint StartingResolution = FIntPoint(50, 50); // DO NOT, I REPEAT, DO NOT MAKE IT 0.
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FVector2D ResolutionStep = FVector2D(1.3, 1.3);

	void MakeXTunnel(int32, int32, int32);
	void MakeYTunnel(int32, int32, int32);
	void FillPath(FIntPoint, FIntPoint);
	void FillRoom(const FRectangle&);

	FRectangle GetRandomRectangle(FIntPoint) const;
	TArray <TArray<TPair<int32, uint64>>> MakeWeighedGraph(TArray<FRectangle>&, int32 = 42);
	TArray<TPair<TPair<int32, int32>, uint64>> GetApproximateMinimalSpanTreeGraph(TArray<FRectangle>& , int32 = 42);
	TArray<FRectangle> GenerateMazeRooms();
	void BuildSurroundingWalls();

};