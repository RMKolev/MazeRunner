// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeRoomGenerator.h"
#include "Maze.h"
// Sets default values
AMazeRoomGenerator::AMazeRoomGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeRoomGenerator::BeginPlay()
{
	Super::BeginPlay();
	this->RStream = FRandomStream(this->WorldSeed);
	if (!this->bUseCustomSeed)
	{
		RStream.GenerateNewSeed();
	}
	if (StartingResolution.X < 5 || StartingResolution.Y < 5)
	{
		UE_LOG(Maze, Error, TEXT("MazeRoomGenerator: Starting Resolution dimensions cannot be less than 5, setting the faulty dimention to 50"));
		if (StartingResolution.X < 5)
		{
			StartingResolution.X = 5;
		}
		if (StartingResolution.Y < 5)
		{
			StartingResolution.Y = 5;
		}
	}
	UE_LOG(Maze, Error, TEXT("%f"), StartingResolution.X);
	if (ResolutionStep.X < 1.2f)
	{
		UE_LOG(Maze, Error, TEXT("MazeRoomGenerator: Resolution Step for X is too small, setting Resolution Step on X to 1.2"));
		ResolutionStep.X = 1.2f;
	}
	UE_LOG(Maze, Error, TEXT("%f"), StartingResolution.X);
	UE_LOG(Maze, Error, TEXT("%f"), StartingResolution.Y);
	if (ResolutionStep.Y < 1.2f)
	{
		UE_LOG(Maze, Error, TEXT("MazeRoomGenerator: Resolution Step for Y is too small, setting Resolution Step on Y to 1.2"));
		ResolutionStep.Y = 1.2f;
	}
	UE_LOG(Maze, Error, TEXT("%f"), StartingResolution.Y);
	BuildMaze();
	LogMazeScheme();
}

void AMazeRoomGenerator::BuildMaze()
{
	TArray<FRectangle> Rooms = GenerateMazeRooms();
	auto MST = GetApproximateMinimalSpanTreeGraph(Rooms);
	for (auto Room : Rooms)
	{
		FillRoom(Room);
	}
	for (auto Path : MST)
	{
		FIntPoint P1 = Rooms[Path.Key.Key].GetNearestPointTo(Rooms[Path.Key.Value]);
		FIntPoint P2 = Rooms[Path.Key.Key].GetNearestPointFrom(Rooms[Path.Key.Value]);
		FillPath(P1, P2);
	}

}

void AMazeRoomGenerator::MakeXTunnel(int32 YCoord, int32 X1, int32 X2)
{
	if (X1 > X2)
	{
		Swap(X1, X2);
	}
	for (int X = X1; X <= X2; ++X)
	{
		if (MazeScheme[YCoord][X] == 0)
			MazeScheme[YCoord][X] = 'p';
	}
}

void AMazeRoomGenerator::MakeYTunnel(int32 XCoord, int32 Y1, int32 Y2)
{
	if (Y1 > Y2)
	{
		Swap(Y1, Y2);
	}
	for (int Y = Y1; Y <= Y2; ++Y)
	{
		if (MazeScheme[Y][XCoord] == 0)
			MazeScheme[Y][XCoord] = 'p';
	}
}

void AMazeRoomGenerator::FillPath(FIntPoint P1, FIntPoint P2)
{
	int flip = rand() % 2;
	if (flip)
	{
		MakeYTunnel(P1.X, P1.Y, P2.Y);
		P1.Y = P2.Y;
		MakeXTunnel(P1.Y, P1.X, P2.X);
	}
	else
	{
		MakeXTunnel(P1.Y, P1.X, P2.X);
		P1.X = P2.X;
		MakeYTunnel(P1.X, P1.Y, P2.Y);
	}
}

void AMazeRoomGenerator::FillRoom(const FRectangle& R)
{
	for (int i = 0; i < R.GetWidth(); ++i)
	{
		for (int j = 0; j < R.GetHeight(); ++j)
		{
			MazeScheme[j + R.GetTopLeft().Y][i + R.GetTopLeft().X] = 'r';
		}
	}
}

void AMazeRoomGenerator::LogMazeScheme() const
{
	FString LoggingScheme;
	LoggingScheme.AppendChar('t');
	LoggingScheme.AppendChar('\n');
	for (auto MazeRow : MazeScheme)
	{
		for (auto MazeCell : MazeRow)
		{
			if (MazeCell != 0)
				LoggingScheme.AppendChar(MazeCell);
			else
				LoggingScheme.AppendChar(' ');
		}
		LoggingScheme.AppendChar('\n');
	}
	UE_LOG(Maze, Warning, TEXT("\n%s"), *LoggingScheme);
}

TArray<FRectangle> AMazeRoomGenerator::GenerateMazeRooms()
{
	TArray<FRectangle> Rooms;

	FIntPoint MazeResolution = StartingResolution;
	int32 NumberOfTries = this->NumberOfRooms * 3;
	while (this->NumberOfRooms > Rooms.Num())
	{
		for (int32 i = NumberOfTries; i > 0 && Rooms.Num() < this->NumberOfRooms; --i)
		{
			FRectangle NewRectangle = GetRandomRectangle(MazeResolution);
			bool bIntersects = false;
			for (auto OldRoom : Rooms)
			{
				if (NewRectangle.IntersectsWith(OldRoom))
				{
					bIntersects = true;
					break;
				}
			}
			if (!bIntersects)
			{
				Rooms.Add(NewRectangle);
			}
		}
		if (Rooms.Num() < this->NumberOfRooms)
		{
			MazeResolution.X *= ResolutionStep.X;
			MazeResolution.Y *= ResolutionStep.Y;

		}
	}
	MazeScheme = TArray<TArray<int8>>();
	MazeScheme.SetNum(MazeResolution.Y);
	for (int i = 0; i < MazeScheme.Num(); ++i)
	{
		MazeScheme[i].SetNumZeroed(MazeResolution.X);
	}
	//UE_LOG(MazeScheme, Warning, TEXT("Successfully created a maze with %d rooms ,maze width %d,maze height %d"), Rooms.Num(), MazeResolution.X, MazeResolution.Y);
	return Rooms;
}

FRectangle AMazeRoomGenerator::GetRandomRectangle(FIntPoint CurrentMazeSize) const
{
	int32 Width = RStream.RandRange(MinimalRoomScale.X, MaximumRoomScale.X);
	int32 Height = RStream.RandRange(MinimalRoomScale.Y, MaximumRoomScale.Y);
	int32 X = RStream.RandRange(0, CurrentMazeSize.X - Width);
	int32 Y = RStream.RandRange(0, CurrentMazeSize.Y - Height);
	return FRectangle(X, Y, Width, Height);
}

TArray<TArray<TPair<int32, uint64>>> AMazeRoomGenerator::MakeWeighedGraph(TArray<FRectangle>& Rooms, int32 NeighborLimit)
{
	Rooms.Sort();
	TArray <TArray<TPair<int32, uint64>>> Result;
	int32 RoomSize = Rooms.Num();
	Result.SetNum(RoomSize - 1);
	for (int32 i = 0; i < RoomSize - 1; ++i)
	{
		int NeighborSize = (RoomSize - i - 1) < NeighborLimit ? (RoomSize - i - 1) : NeighborLimit;
		Result[i].SetNum(NeighborSize);
		for (int32 j = 1; j <= NeighborSize; ++j)
		{
			uint64 Distance = Rooms[i].GetDistanceSquaredTo(Rooms[i + j]);
			Result[i][j - 1] = TPair<int32, uint64>(i + j, Distance);
		}
	}
	int i = 0;
	/*for (auto P : Result) {
		UE_LOG(Maze, Warning, TEXT("From Rib: %d"), i);
		for (auto T : P) {
			UE_LOG(Maze, Warning, TEXT("To rib %d -> %d"), T.Key, T.Value);
		}
		++i;
	}*/
	return Result;
}

TArray<TPair<TPair<int32, int32>, uint64>> AMazeRoomGenerator::GetApproximateMinimalSpanTreeGraph(TArray<FRectangle>& Rooms, int32 NeighborLimit)
{
	auto WeighedGraph = MakeWeighedGraph(Rooms, NeighborLimit);
	TArray<int32> Indexes;
	TArray<TPair<TPair<int32, int32>, uint64>> MST;
	Indexes.Add(0);
	while (Indexes.Num() != Rooms.Num())
	{
		auto NewRib = TPair<TPair<int32, int32>, uint64>(TPair< int32, int32>(-1, -1), 0);
		for (int32 i = 0; i < Indexes.Num(); ++i)
		{
			if (Indexes[i] < WeighedGraph.Num())
			{
				for (int32 j = 0; j < WeighedGraph[Indexes[i]].Num(); ++j)
				{
					auto RibK = WeighedGraph[Indexes[i]][j];
					bool bVisited = false;
					for (int32 Visited : Indexes)
					{
						if (Visited == RibK.Key)
						{
							bVisited = true;
						}
					}
					if (!bVisited && (NewRib.Value > RibK.Value || (NewRib.Key.Key == -1)))
					{
						int32 NewDest = RibK.Key;
						uint64 NewWeight = RibK.Value;
						NewRib = TPair<TPair<int32, int32>, uint64>(TPair< int32, int32>(Indexes[i], NewDest), NewWeight);
					}
				}
			}
		}
		if (NewRib.Key.Key != -1)
		{
			MST.Add(NewRib);
			Indexes.Add(NewRib.Key.Value);
		}
	}
	for (TPair<TPair<int32, int32>, uint64> K : MST)
	{
		UE_LOG(Maze, Warning, TEXT("%d -> %d : %d"), K.Key.Key, K.Key.Value, K.Value);
	}
	return MST;
}

// Called every frame
void AMazeRoomGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

