// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCaveGenerator.h"
#include "Maze.h"
#include "Containers/Queue.h"

void AMazeCaveGenerator::BeginPlay()
{
	if (bUseCustomSeed)
	{
		SetSeed(WorldSeed);
	}
	else
	{
		RStream.GenerateNewSeed();
	}

	BuildMaze();
}

void AMazeCaveGenerator::TransferCave()
{
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			PrevCaveIteration[i][j] = MazeScheme[i][j];
		}
	}
}

void AMazeCaveGenerator::RandomFill()
{
	if (!CharacterMap.Contains(FName("Floor")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room Floors"));
		return;
	}
	int8 FloorCharacter = CharacterMap.FindChecked(FName("Floor"));
	if (!CharacterMap.Contains(FName("Wall")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room walls"));
		return;
	}
	int8 WallCharacter = CharacterMap.FindChecked(FName("Wall"));

	UE_LOG(Maze, Warning, TEXT("Floor Character: %d  Wall Character: %d"), FloorCharacter, WallCharacter);
	for (int32 i = 0; i < Height; ++i)
	{
		MazeScheme[i][0] = WallCharacter;
		MazeScheme[i][Width - 1] = WallCharacter;
	}
	for (int32 j = 0; j < Width; ++j)
	{
		MazeScheme[0][j] = WallCharacter;
		MazeScheme[Height - 1][j] = WallCharacter;
	}
	for (int32 i = 1; i < Height - 1; ++i)
	{
		for (int32 j = 1; j < Width - 1; ++j)
		{
			MazeScheme[i][j] = RStream.RandRange(0, 100) > FillPercentige ? FloorCharacter : WallCharacter;
		}
	}
}

int32 AMazeCaveGenerator::GetNeighbourWallCount(int32 CurrI, int32 CurrJ,const TArray<TArray<int8>>& ToCheck) const
{
	if (!CharacterMap.Contains(FName("Wall")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room walls"));
		return -1;
	}
	int8 WallCharacter = CharacterMap.FindChecked(FName("Wall"));

	int32 WallCount = 0;
	for (int32 i = CurrI - 1; i <= CurrI + 1; ++i)
	{
		for (int32 j = CurrJ - 1; j <= CurrJ + 1; ++j)
		{
			if (i >= 0 && i < Height && j >= 0 && j < Width)
			{
				if (i != CurrI || j != CurrJ)
				{
					WallCount = WallCount + (ToCheck[i][j] == WallCharacter);
				}
			}
			else ++WallCount;
		}
	}

	return WallCount;
}

void AMazeCaveGenerator::SmoothingIteration()
{
	if (!CharacterMap.Contains(FName("Floor")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room Floors"));
		return;
	}
	int8 FloorCharacter = CharacterMap.FindChecked(FName("Floor"));
	if (!CharacterMap.Contains(FName("Wall")))
	{
		UE_LOG(Maze, Error, TEXT("AMazeCaveGenerator::RandomFill() - No character for room walls"));
		return;
	}
	int8 WallCharacter = CharacterMap.FindChecked(FName("Wall"));

	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			int32 WallCount = GetNeighbourWallCount(i, j, PrevCaveIteration);
			if (WallCount > 4) MazeScheme[i][j] = WallCharacter;
			if (WallCount < 4) MazeScheme[i][j] = FloorCharacter;
		}
	}
}

TArray<FIntPoint> AMazeCaveGenerator::GetRegionByTile(int32 StartI, int32 StartJ)
{
	TArray<FIntPoint> Tiles;
	int8 TileType = MazeScheme[StartI][StartJ];
	TQueue<FIntPoint> Queue;
	Queue.Enqueue(FIntPoint(StartI, StartJ));
	PrevCaveIteration[StartI][StartJ] = 1;

	while (!Queue.IsEmpty())
	{
		FIntPoint Curr; 
		Queue.Dequeue(Curr);
		Tiles.Add(Curr);

		// Check neighbours
		for (int32 i = Curr.X - 1; i <= Curr.X + 1; ++i)
		{
			for (int32 j = Curr.Y - 1; j <= Curr.Y + 1; ++j)
			{
				if (i >= 0 && i < Height && j >= 0 && j < Width)
				{
					if (PrevCaveIteration[i][j] == 0 && MazeScheme[i][j] == TileType)
					{
						PrevCaveIteration[i][j] = 1;
						Queue.Enqueue(FIntPoint(i, j));
					}
				}
			}
		}
		
	}
	return Tiles;
}

TArray<TArray<FIntPoint>> AMazeCaveGenerator::GetRegions(int8 TileType)
{
	TArray<TArray<FIntPoint>> Regions;
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			if (PrevCaveIteration[i][j] == 0 && MazeScheme[i][j] == TileType)
			{
				TArray<FIntPoint> NewRegion = GetRegionByTile(i, j);
				Regions.Add(NewRegion);
			}
		}
	}
	
	return Regions;
}

void AMazeCaveGenerator::ProcessMazeScheme()
{
	// Reuses PrevCaveIteration to show which tiles have been visited
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			PrevCaveIteration[i][j] = 0;
		}
	}

	// Find all regions
	TArray<TArray<FIntPoint>> FloorRegions = GetRegions(CharacterMap.FindChecked(FName("Floor")));
	TArray<TArray<FIntPoint>> SurvivingRegions;
	for (int32 i = 0; i < FloorRegions.Num(); ++i)
	{
		if (FloorRegions[i].Num() < FloorRegionThreshold)
		{
			for (FIntPoint Coord : FloorRegions[i])
			{
				MazeScheme[Coord.X][Coord.Y] = CharacterMap.FindChecked(FName("Wall"));
			}
		}
		else
		{
			SurvivingRegions.Add(FloorRegions[i]);
		}
	}

	// Find the edge tiles of the regions
	TArray<TArray<FIntPoint>> EdgeTilesOfRegions;
	EdgeTilesOfRegions.SetNum(SurvivingRegions.Num());
	for (int32 i = 0; i < SurvivingRegions.Num(); ++i)
	{
		for (int32 j = 0; j < SurvivingRegions[i].Num(); ++j)
		{
			if (GetNeighbourWallCount(i, j, MazeScheme) > 0)
			{
				EdgeTilesOfRegions[i].Add(SurvivingRegions[i][j]);
			}
		}
	}

	// Find edges from each region to all other regions
	TArray<Edge> RegionEdges;
	for (int i = 0; i < EdgeTilesOfRegions.Num() - 1; ++i)
	{
		for (int j = i + 1; j < EdgeTilesOfRegions.Num(); ++j)
		{
			Edge ShortestEdge(i, j, EdgeTilesOfRegions[i][0], EdgeTilesOfRegions[j][0],
				(EdgeTilesOfRegions[i][0].X - EdgeTilesOfRegions[j][0].X) * (EdgeTilesOfRegions[i][0].X - EdgeTilesOfRegions[j][0].X) +
				(EdgeTilesOfRegions[i][0].Y - EdgeTilesOfRegions[j][0].Y) * (EdgeTilesOfRegions[i][0].Y - EdgeTilesOfRegions[j][0].Y));
			for (int k = 0; k < EdgeTilesOfRegions[i].Num(); ++k)
			{
				for (int l = 0; l < EdgeTilesOfRegions[j].Num(); ++l)
				{
					Edge CurrEdge(i, j, EdgeTilesOfRegions[i][k], EdgeTilesOfRegions[j][l],
						(EdgeTilesOfRegions[i][k].X - EdgeTilesOfRegions[j][l].X) * (EdgeTilesOfRegions[i][k].X - EdgeTilesOfRegions[j][l].X) +
						(EdgeTilesOfRegions[i][k].Y - EdgeTilesOfRegions[j][l].Y) * (EdgeTilesOfRegions[i][k].Y - EdgeTilesOfRegions[j][l].Y));
					if (CurrEdge < ShortestEdge)
					{
						ShortestEdge = CurrEdge;
					}
				}
			}
			RegionEdges.Add(ShortestEdge);			
		}
	}

	// Build MST which shows which edges need to be used to connect all regions
	TArray<Edge> MST = Kruskal(EdgeTilesOfRegions.Num(),RegionEdges);
	for (Edge Curr : MST)
	{
		CreatePassage(Curr.RegionA, Curr.RegionB, Curr.PointA, Curr.PointB);
	}

	if (WallRegionThreshold > 0)
	{
		TArray<TArray<FIntPoint>> WallRegions = GetRegions(CharacterMap.FindChecked(FName("Wall")));
		for (int32 i = 0; i < WallRegions.Num(); ++i)
		{
			if (WallRegions[i].Num() < WallRegionThreshold)
			{
				for (FIntPoint Coord : WallRegions[i])
				{
					MazeScheme[Coord.X][Coord.Y] = CharacterMap.FindChecked(FName("Floor"));
				}
			}
		}
	}
}

void AMazeCaveGenerator::UnionTrees(int32 From, int32 To, TArray<int32>& Rank, TArray<int32>& Parent)
{
	if (Rank[From] == Rank[To])
	{
		Parent[To] = From;
		Rank[From]++;
	}
	else if (Rank[From] < Rank[To])
	{
		Parent[From] = To;
	}
	else
	{
		Parent[To] = From;
	}
}

int32 AMazeCaveGenerator::UnionFind(int32 Node, TArray<int32>& Parent)
{
	if (Parent[Node] == Node)
	{
		return Node;
	}

	return Parent[Node] = UnionFind(Parent[Node], Parent);
}

TArray<Edge> AMazeCaveGenerator::Kruskal(int32 NumOfNodes, TArray<Edge>& Edges)
{
	TArray<int32> Parent;
	TArray<int32> Rank;
	TArray<Edge> MST;
	Edges.Sort();
	Parent.SetNum(Edges.Num());
	Rank.SetNum(Edges.Num());
	for (int i = 0; i < NumOfNodes; ++i)
	{
		Parent[i] = i;
		Rank[i] = 0;
	}
	int Ind = 0, Count = 0;
	while (Count < NumOfNodes - 1)
	{
		int P1 = UnionFind(Edges[Ind].RegionA, Parent);
		int P2 = UnionFind(Edges[Ind].RegionB, Parent);
		if (P1 != P2)
		{
			UnionTrees(P1, P2, Rank, Parent);
			Count++;
			MST.Add(Edges[Ind]);
			UE_LOG(Maze, Warning, TEXT("ShortestEdges %d %d %d %d %d %d %d"), Edges[Ind].RegionA, Edges[Ind].RegionB,
				Edges[Ind].PointA.X, Edges[Ind].PointA.Y, Edges[Ind].PointB.X, Edges[Ind].PointB.Y, Edges[Ind].Distance);
		}
		Ind++;
	}
	return MST;
}

TArray<FIntPoint> AMazeCaveGenerator::GetLine(FIntPoint From, FIntPoint To)
{
	TArray<FIntPoint> Line;
	if (From.X == To.X)
	{
		for (int i = FMath::Min(From.Y, To.Y); i <= FMath::Max(From.Y, To.Y); ++i)
		{
			Line.Add(FIntPoint(From.X,i));
		}
	}
	else if (From.Y == To.Y)
	{
		for (int i = FMath::Min(From.X, To.X); i <= FMath::Max(From.X, To.X); ++i)
		{
			Line.Add(FIntPoint(i, From.Y));
		}
	}
	else
	{
		int32 X = From.X;
		int32 Y = From.Y;
		int32 Dx = To.X - From.X;
		int32 Dy = To.Y - From.Y;
		bool bInverted = false;
		int32 Step = FMath::Sign(Dx);
		int32 GradientStep = FMath::Sign(Dy);
		int32 Longest = FMath::Abs(Dx);
		int32 Shortest = FMath::Abs(Dy);

		if (Longest > Shortest)
		{
			bInverted = true;
			Swap(Longest, Shortest);
			Swap(Step, GradientStep);
		}

		int32 GradientAccumulation = Longest / 2;
		for (int i = 0; i < Longest; ++i)
		{
			Line.Add(FIntPoint(X, Y));
			if (bInverted)
			{
				Y += Step;
			}
			else
			{
				X += Step;
			}

			GradientAccumulation += Shortest;
			if (GradientAccumulation >= Longest)
			{
				if (bInverted)
				{
					X += GradientStep;
				}
				else
				{
					Y += GradientStep;
				}
				GradientAccumulation -= Longest;
			}
		}
	}
	return Line;
}

void AMazeCaveGenerator::DrawInRadius(FIntPoint Center, int32 Radius)
{
	for (int i = -Radius; i <= Radius; ++i)
	{
		for (int j = -Radius; j <= Radius; ++j)
		{
			if (i * i + j * j <= Radius * Radius)
			{
				int RealI = Center.X + i;
				int RealJ = Center.Y + j;
				if (RealI > 0 && RealI < Height - 1 && RealJ > 0 && RealJ < Width - 1)
				{
					MazeScheme[RealI][RealJ] = CharacterMap.FindChecked(FName("Floor"));
				}
			}
		}
	}
}

void AMazeCaveGenerator::CreatePassage(int32 RegionA, int32 RegionB, FIntPoint PointA, FIntPoint PointB)
{
	TArray<FIntPoint> Line = GetLine(PointA, PointB);

	for (FIntPoint Point : Line)
	{
		DrawInRadius(Point, 3);
	}
}

void AMazeCaveGenerator::BuildMaze()
{
	MazeScheme.SetNum(Height);
	PrevCaveIteration.SetNum(Height);
	for (int32 i = 0; i < Height; ++i)
	{
		MazeScheme[i].SetNum(Width);
		PrevCaveIteration[i].SetNum(Width);
	}

	RandomFill();
	for (int32 i = 0; i < NumberOfIterations; ++i)
	{
		TransferCave();
		SmoothingIteration();
	}
	ProcessMazeScheme();
}
