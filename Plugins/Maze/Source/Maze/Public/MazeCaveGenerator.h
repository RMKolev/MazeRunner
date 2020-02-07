// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeGenerator.h"
#include "MazeCaveGenerator.generated.h"

/**
 * 
 */

struct Edge
{
	int32 RegionA;
	int32 RegionB;
	FIntPoint PointA;
	FIntPoint PointB;
	int32 Distance;
	
	Edge(int32 RegionA, int32 RegionB, FIntPoint PointA, FIntPoint PointB, int32 Distance) :
		RegionA(RegionA), RegionB(RegionB), PointA(PointA), PointB(PointB), Distance(Distance)
	{}
	bool operator<(const Edge& Other) const
	{
		return Distance < Other.Distance;
	}
};

UCLASS()
class MAZE_API AMazeCaveGenerator : public AMazeGenerator
{
	GENERATED_BODY()

public:
	virtual void BuildMaze() override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 Height = 25;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 Width = 25;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 FillPercentige = 45;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 NumberOfIterations = 5;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 WallRegionThreshold = 0;

	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 FloorRegionThreshold = 0;

	TArray<TArray<int8>> PrevCaveIteration;

	void TransferCave();
	void RandomFill();
	int32 GetNeighbourWallCount(int32 CurrI, int32 CurrJ, const TArray<TArray<int8>>& ToCheck) const;
	void SmoothingIteration();
	TArray<FIntPoint> GetRegionByTile(int32 StartX, int32 StartY);
	TArray<TArray<FIntPoint>> GetRegions(int8 TileType);
	void ProcessMazeScheme();
	TArray<FIntPoint> GetLine(FIntPoint From, FIntPoint To);
	void CreatePassage(int32 RegionA, int32 RegionB, FIntPoint PointA, FIntPoint PointB);
	void DrawInRadius(FIntPoint Center, int32 Radius);

	void UnionTrees(int32 From, int32 To, TArray<int32>& Rank, TArray<int32>& Parent);
	int32 UnionFind(int32 Node, TArray<int32>& Parent);
	TArray<Edge> Kruskal(int32 NumOfNodes, TArray<Edge>& Edges);
};


