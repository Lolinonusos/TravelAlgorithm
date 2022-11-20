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
	
}

// Called every frame
void AMyVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyVertex::SetSartMat() {
	SphereMesh->SetMaterial(0, StartMaterial);
}

void AMyVertex::SetUnvisitedMat() {
	SphereMesh->SetMaterial(0, UnvisitedMaterial);
}

void AMyVertex::SetVisitedMat() {
	SphereMesh->SetMaterial(0, VisitedMaterial);
}

void AMyVertex::SetEndMat() {
	SphereMesh->SetMaterial(0, EndMaterial);
}
