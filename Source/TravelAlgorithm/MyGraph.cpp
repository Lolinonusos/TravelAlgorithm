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
	
	int32 VertexTotal = 20;
	
	UWorld* World = GetWorld();
	if (World)
	{
		{
			for (int i = 0; i < VertexTotal; i++) {
				AMyVertex* NewVertex = World->SpawnActor<AMyVertex>(BP_Vertex,
					FVector(FMath::RandRange(-500.0f,500.0f),FMath::RandRange(-500.0f,500.0f), FMath::RandRange(0.0f,1000.0f)),
					FRotator(0.0f, 0.0f, 0.0f));
				// UE_LOG(LogTemp, Warning, TEXT("Hello %d"), i);
				if (NewVertex) {
					VertList.Add(NewVertex);
					if (i == 0) {
						VertList[i]->SetSartMat();
					}
					if (i == VertexTotal - 1) {
						VertList[i]->SetEndMat();
					}
					else {
						VertList[i]->SetUnvisitedMat();
					}
				}
			}
		}
		EdgeSetup();

		Dijkstra(VertList[0], VertList[VertList.Num() - 1]);
	}
}




// Called every frame
void AMyGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyGraph::EdgeSetup() {
	for (int i = 0; i < 100; i++) {
		
		int32 RandSrc = FMath::RandRange(0,VertList.Num() - 1);
		int32 RandDest = FMath::RandRange(0,VertList.Num() - 1);
		
		VertList[RandSrc]->Edge = VertList[RandDest];
		VertList[RandSrc]->Edge->Weight = FVector::Dist(VertList[RandSrc]->GetActorLocation(), VertList[RandDest]->GetActorLocation());
		VertList[RandDest]->ReverseEdge = VertList[RandSrc];
		VertList[RandDest]->ReverseEdge->Weight = FVector::Dist(VertList[RandDest]->GetActorLocation(), VertList[RandSrc]->GetActorLocation());

		VertList[RandSrc]->EdgeList.Add(VertList[RandSrc]->Edge);
		VertList[RandDest]->EdgeList.Add(VertList[RandDest]->ReverseEdge);
		
		DrawDebugLine(GetWorld(), VertList[RandSrc]->GetActorLocation(), VertList[RandDest]->GetActorLocation(), FColor::White,
			true, -1, 0, 1);
	}
}

void AMyGraph::Dijkstra(AMyVertex* StartVert, AMyVertex* EndVert) {

	//TQueue<int> Q;

	
	//TMap<float, float> Visited = {};
	TMap<float, AMyVertex*> Unvisited;

	
	for (int i = 0; i < VertList.Num(); i++) {
		if (VertList[i] != StartVert) {
			VertList[i]->Distance = 99999;
			VertList[i]->bVisited = false;
			VertList[i]->PreviousVert = nullptr;
			//Unvisited.Emplace(VertList[i]->Distance, 0); // Infinity
		}
	}
	VertList[18]->Edge = EndVert;
	
	StartVert->Distance = 0;
	StartVert->bVisited = true;
	StartVert->PreviousVert = nullptr;
	AMyVertex* CurrentVert = StartVert;

	if (StartVert == nullptr) {
		return;
	}
	if (EndVert == nullptr) {
		return;
	}
	
	Unvisited.Find(StartVert->Distance);
	int k = 0;
	if (CurrentVert) {
		
	while (EndVert->bVisited != true) {
	 	//k++;
	 	// Check value of Edges pointing to neighbours
	 	//int MinVal = Unvisited[0];
	 	for (int i = 0; i < CurrentVert->EdgeList.Num(); i++) {
	 		if (CurrentVert->EdgeList[i] && CurrentVert->EdgeList[i]->bVisited != true) {
	 			TotalDistance = CurrentVert->Edge->Distance + CurrentVert->Distance;
	
	 			Unvisited.Emplace(CurrentVert->Edge->Distance, CurrentVert->Edge);
	
	 			if (TotalDistance < CurrentVert->Edge->Distance) {
	 				CurrentVert->Edge->Distance = TotalDistance;
	 				CurrentVert->Edge->PreviousVert = CurrentVert;
	 			}
	 		}
	 	}
	
	 	if (Unvisited.begin()) {
	 		Unvisited.KeySort([](float A, float B) {return A < B;});
	 		CurrentVert = Unvisited.begin().Value();
	
	 		Unvisited.Remove(Unvisited.begin().Key());
	
	 	}
	 	CurrentVert->bVisited = true;
	 	CurrentVert->SetVisitedMat();
		}
	}

	AMyVertex* DrawPath = EndVert;
	while(DrawPath->PreviousVert != nullptr) {
		
	 	DrawDebugLine(GetWorld(),DrawPath->GetActorLocation(),DrawPath->PreviousVert->GetActorLocation(),FColor::Green,true,-1,0,3);
	 	
	 	DrawPath = DrawPath->PreviousVert;
	}
	
	
}

int AMyGraph::AStar() {

	
	return 1;
}

void AMyGraph::ReconstructPath() {
}
