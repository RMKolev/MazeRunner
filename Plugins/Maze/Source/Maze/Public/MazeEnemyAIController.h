// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MazeEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeEnemyAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviourComp;

public:

	AMazeEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;

	uint8 EnemyKeyID;
	
};
