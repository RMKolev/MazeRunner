// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_UpdateRandomLocation.h"
#include "MazeEnemyAIController.h"

EBTNodeResult::Type UBTTask_UpdateRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMazeEnemyAIController* MazeEnemyAIController = Cast<AMazeEnemyAIController>(OwnerComp.GetOwner());

	if (IsValid(MazeEnemyAIController) == false)
	{
		return EBTNodeResult::Failed;
	}

	MazeEnemyAIController->ChooseRandomPoint();

	return EBTNodeResult::Succeeded;
}
