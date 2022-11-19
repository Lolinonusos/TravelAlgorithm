// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGraph.h"

//#include "Math/UnrealMathUtility.h"

// Sets default values
AMyGraph::AMyGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}


// Called when the game starts or when spawned
void AMyGraph::BeginPlay() {
	Super::BeginPlay();

	// Randomize vertex positions
	// for (int i = 0; i < Vertex.Num(); i++) {
	// 	Vertex[i]->SetWorldLocation(FVector(FMath::RandRange(0.0f, 100.0f), FMath::RandRange(0.0f, 100.0f), FMath::RandRange(0.0f, 100.0f)));
	// }
	int32 VertexTotal = 20;
	
	UWorld* World = GetWorld();
	if (World)
	{
		{
			for (int i = 0; i < VertexTotal; i++) {
				AMyVertex* NewVertex = World->SpawnActor<AMyVertex>(BP_Vertex,
					FVector(FMath::RandRange(-500.0f,500.0f),FMath::RandRange(-500.0f,500.0f), FMath::RandRange(0.0f,1000.0f)),
					FRotator(0.0f, 0.0f, 0.0f));
					UE_LOG(LogTemp, Warning, TEXT("Hello %d"), i);
				if (NewVertex) {
					VertList.Add(NewVertex);
					if (i == 0) {
						
					}
					if (i == VertexTotal) {
						
					}
				}
			}
		}
	
		// for (int i = 0; i < VertList.Num(); i++) {
		// 	VertList[i]->SetActorLocation(FVector(FMath::RandRange(-500.0f,500.0f), FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(-500.0f, 500.0f)));		
		// }

	
		EdgeSetup(1,1,1);
		// AdjacencyMatrix.Reset(VertexAmount);
		// for (int i = 0; i < AdjacencyMatrix.Num(); i++) {
		// 	AdjacencyMatrix[i].InnerMatrix.Reset(VertexAmount);
		// }
	}
}

int AMyGraph::Dijkstra() {

	TQueue<int> Q;

	for (int i = 0; i < 19; i++) {
		
	}
	
	return 1;
}

int AMyGraph::AStar() {

	return 1;
}


// Called every frame
void AMyGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyGraph::MatrixSetup() {
}

void AMyGraph::EdgeSetup(int SourceVert, int DestVert, float EdgeWeight) {
	for (int i = 0; i < 50; i++) {
		
		int32 RandSrc = FMath::RandRange(0,VertList.Num() - 1);
		int32 RandDest = FMath::RandRange(0,VertList.Num() - 1);
		
		VertList[RandSrc]->Edge = VertList[RandDest];
		VertList[RandSrc]->Edge->Weight = FVector::Dist(VertList[RandSrc]->GetActorLocation(), VertList[RandDest]->GetActorLocation());

		DrawDebugLine(GetWorld(), VertList[RandSrc]->GetActorLocation(), VertList[RandDest]->GetActorLocation(), FColor::Red,
			true, -1, 0, 3);
	}
}

