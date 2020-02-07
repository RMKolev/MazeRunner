// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Math/Vector.h"
#include "MazeEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeEnemyAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY()
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	class UBehaviorTreeComponent* BehaviourTreeComp;

	UPROPERTY(EditAnywhere, Category = MazeProperties)
	class UBehaviorTree* BehaviourTree;

public:

	FVector DestLocation;

	AMazeEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;

	void ActivateRoaming();

	void ChooseRandomPoint();

	//virtual void FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const override;
	   
//	uint8 EnemyKeyID;
	
};
