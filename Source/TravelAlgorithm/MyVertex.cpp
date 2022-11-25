// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVertex.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AMyVertex::AMyVertex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereMesh->SetupAttachment(GetRootComponent());

	// Materials
	StartMaterial = CreateDefaultSubobject<UMaterial>(TEXT("StartMaterial"));
	UnvisitedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("UnvisitedMaterial"));
	VisitedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("VisitedMaterial"));
	EndMaterial = CreateDefaultSubobject<UMaterial>(TEXT("EndMaterial"));
}

// Called when the game starts or when spawned
void AMyVertex::BeginPlay()
{
	Super::BeginPlay();

	Weight = FMath::RandRange(1, 10);
	
}

// Called every frame
void AMyVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyVertex::SetStartMat() {
	SphereMesh->SetMaterial(0, StartMaterial); // Copper
}

void AMyVertex::SetUnvisitedMat() {
	SphereMesh->SetMaterial(0, UnvisitedMaterial); // Rusted
}

void AMyVertex::SetVisitedMat() {
	SphereMesh->SetMaterial(0, VisitedMaterial); // Silver/steel
}

void AMyVertex::SetEndMat() {
	SphereMesh->SetMaterial(0, EndMaterial); // Golden
}
