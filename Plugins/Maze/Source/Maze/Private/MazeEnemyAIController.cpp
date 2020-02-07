// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MazeBuilder.h"
#include "MazeGenerator.h"
#include "Math/UnrealMathUtility.h"
#include "MazeEnemyCharacter.h"

AMazeEnemyAIController::AMazeEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviourTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}

void AMazeEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(BehaviourTree))
	{
		BlackboardComp->InitializeBlackboard(*BehaviourTree->BlackboardAsset);
		BehaviourTreeComp->StartTree(*BehaviourTree);
	}
}

void AMazeEnemyAIController::ChooseRandomPoint()
{
//	AMazeGenerator* RoombasedMaze = GetWorld()->SpawnActor<AMazeGenerator>();
//	TArray<TArray<bool>> Terrain = RoombasedMaze->GetWalkableTerrain();

//	int32 Rand_i, Rand_j;

//	do
//	{
//		Rand_i = FMath::RandRange(0, Terrain.Num() - 1);
//		Rand_j = FMath::RandRange(0, Terrain[0].Num() - 1);

//	} while (!Terrain[Rand_i][Rand_j]);

//	FIntPoint RandPoint = FIntPoint(Rand_i, Rand_j);

	FVector OldLoc = this->GetPawn()->GetActorLocation();

	int32 RandX = FMath::RandRange(-1000, 1000);
	int32 RandY = FMath::RandRange(-1000, 1000);

	FVector RandLocation(OldLoc.X + RandX, OldLoc.Y + RandY, OldLoc.Z);
	
	//FVector RandLocation = FMazeBasis().GetMazePointLocation(RandPoint);

	BlackboardComp->SetValueAsVector("RandomLocation", RandLocation);
}

