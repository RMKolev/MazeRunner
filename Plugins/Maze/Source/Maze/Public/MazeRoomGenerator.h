// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rectangle.h"
#include "GameFramework/Actor.h"
#include "MazeRoomGenerator.generated.h"

UCLASS()
class MAZE_API AMazeRoomGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeRoomGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Category=AlgorithmProperties,EditAnywhere)
		uint64 WorldSeed;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		bool bUseCustomSeed;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 NumberOfRooms;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint MinimalRoomScale;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint MaximumRoomScale;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint StartingResolution = FIntPoint(50,50); // DO NOT, I REPEAT, DO NOT MAKE IT 0.
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FVector2D ResolutionStep = FVector2D(1.3,1.3);

		TArray<TArray<int8>> MazeScheme;
	UPROPERTY()
	FRandomStream RStream;

public:
	void BuildMaze();
	void MakeXTunnel(int32, int32, int32);
	void MakeYTunnel(int32, int32, int32);
	void FillPath(FIntPoint, FIntPoint);
	void FillRoom(const FRectangle&);
	void LogMazeScheme() const;
	TArray<FRectangle> GenerateMazeRooms();
	TArray<TArray<char>> GetMaze() const;
	TArray<TArray<char>> GetPaths() const;
	TArray<TArray<char>> GetRooms() const;
	FRectangle GetRandomRectangle(FIntPoint) const;
	TArray <TArray<TPair<int32, uint64>>> MakeWeighedGraph(TArray<FRectangle>&, int32 = 42);
	TArray<TPair<TPair<int32, int32>, uint64>> GetApproximateMinimalSpanTreeGraph(TArray<FRectangle>& rectangles, int32 neighborLimit = 42);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
