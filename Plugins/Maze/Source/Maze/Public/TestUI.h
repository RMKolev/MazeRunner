// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestUI.generated.h"

UCLASS()
class MAZE_API ATestUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY()
	int32 RandomInt_1;

	UPROPERTY()
	int32 RandomInt_2;

	UPROPERTY()
	float RandomFloat;

	UPROPERTY()
	TArray<int32> RandomIntegers;

	ATestUI();
	void Init(int32 a, int32 b, float c, TArray<int32> d);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
