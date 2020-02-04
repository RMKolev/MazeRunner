// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUI.h"
#include "Logging/LogVerbosity.h"

// Sets default values
ATestUI::ATestUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATestUI::Init(int32 a, int32 b, float c, TArray<int32> d)
{
	RandomInt_1 = a;
	RandomInt_2 = b;
	RandomFloat = c;
	RandomIntegers = d;
}

// Called when the game starts or when spawned
void ATestUI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestUI::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FString ChangedProperty = PropertyChangedEvent.Property->GetFName().ToString();

	UE_LOG(LogTemp, Warning, TEXT("A property was changed: %s"), *ChangedProperty);
}

