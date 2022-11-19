// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVertex.h"


#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyVertex::AMyVertex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereMesh->SetupAttachment(GetRootComponent());
	
	// Vertex.Init(nullptr, 6);
	//
	// Vertex[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VertexMoment0"));
	// Vertex[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VertexMoment1"));
	// Vertex[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VertexMoment2"));
	// Vertex[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VertexMoment3"));
	// Vertex[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VertexMoment4"));
	// Vertex[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VertexMoment5"));

	// Materials
	StartMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Blue"));
	UnvisitedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("White"));
	VisitedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Red"));
	EndMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Green"));
	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>VertexMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	
	// for (int i = 0; i < Vertex.Num(); i++) {
	// 	if (i == 0) {
	// 		Vertex[0]->SetMaterial(0, StartMaterial);
	// 	}
	// 	else if (i == Vertex.Num()) {
	// 		Vertex[Vertex.Num()]->SetMaterial(3, EndMaterial);
	// 	}
	// 	else {
	// 		Vertex[i]->SetMaterial(1, UnvisitedMaterial);
	// 	}
	// }
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

