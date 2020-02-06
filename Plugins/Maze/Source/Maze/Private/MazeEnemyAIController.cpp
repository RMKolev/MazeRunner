// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MazeEnemyCharacter.h"

AMazeEnemyAIController::AMazeEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}

void AMazeEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMazeEnemyCharacter* Character = Cast<AMazeEnemyCharacter>(InPawn);

	if (Character && Character->BotBehaviour)
	{
		Blackboard->InitializeBlackboard(*Character->BotBehaviour->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviourComp->StartTree(*Character->BotBehaviour);
	}
}
