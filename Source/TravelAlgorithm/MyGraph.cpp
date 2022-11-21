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
		//EdgeSetup();

		TSP(VertList[0]);

		//Dijkstra(VertList[0], VertList[VertList.Num() - 1]);
	}
}




// Called every frame
void AMyGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyGraph::EdgeSetup() {
	for (AMyVertex* Vert : VertList) { // Different way of for looping: for (*Datatype of Array* newName : Array)
		int RandEdgeAmount = FMath::RandRange(2,6);
		for (int i = 0; i < RandEdgeAmount; i++) {
			int RandVert = FMath::RandRange(0,VertList.Num() - 1);
			
			Vert->EdgeList.Emplace(VertList[RandVert]);
			DrawDebugLine(GetWorld(), Vert->GetActorLocation(), VertList[RandVert]->GetActorLocation(),
				FColor::White,true, -1, 0, 1);
		}
	}
	
	// for (int i = 0; i < VertList.Num(); i++) {
	// 	
	// 	int32 RandSrc = FMath::RandRange(0,VertList.Num() - 1);
	// 	int32 RandDest = FMath::RandRange(0,VertList.Num() - 1);
	// 	
	// 	VertList[RandSrc]->EdgeList.Emplace(VertList[RandDest]);
	// 	VertList[RandSrc]->EdgeList[RandDest]->Weight = FVector::Dist(VertList[RandSrc]->GetActorLocation(), VertList[RandDest]->GetActorLocation());
	//
	// 	VertList[RandDest]->EdgeList.Emplace(VertList[RandSrc]);
	// 	VertList[RandDest]->EdgeList[RandSrc]->Weight = FVector::Dist(VertList[RandDest]->GetActorLocation(), VertList[RandSrc]->GetActorLocation());
	//
	// 	VertList[RandSrc]->EdgeList.Add(VertList[RandSrc]->Edge);
	// 	VertList[RandDest]->EdgeList.Add(VertList[RandDest]->ReverseEdge);
	// 	
	// 	DrawDebugLine(GetWorld(), VertList[RandSrc]->GetActorLocation(), VertList[RandDest]->GetActorLocation(), FColor::White,
	// 		true, -1, 0, 1);
	// }
}

void AMyGraph::TSP(AMyVertex* Start) {

	AMyVertex* CurrentVert = Start;
	CurrentVert->bVisited = true;
	AMyVertex* ShortestDistptr = nullptr;

	
	//TMap<AMyVertex*, float> Unvisited;
	TArray<AMyVertex*> UnvisitedArr;
	
	for(int i = 0; i < VertList.Num(); i++) {
		VertList[i]->PreviousVert = nullptr;
		if (VertList[i]->bVisited != true) {

			UnvisitedArr.Add(VertList[i]);
		}
	}

	bool allVisited = false;
	
	while (allVisited == false) {

		CurrentVert->bVisited = true;
		float ShortestDist = 99999;
		int visitedCounter = 0;
		
		for(int i = 0; i < UnvisitedArr.Num(); i++) {

			float VertDistance = FVector::Distance(CurrentVert->GetActorLocation(), UnvisitedArr[i]->GetActorLocation());

			if (ShortestDist > VertDistance && UnvisitedArr[i]->bVisited == false) {
				ShortestDist = VertDistance;
				ShortestDistptr = UnvisitedArr[i];
			}
			
			if (UnvisitedArr[i]->bVisited == true) {
				visitedCounter += 1;
				if (visitedCounter == UnvisitedArr.Num() - 1) {
					allVisited = true;
				}
			}
		}
		CurrentVert->EdgeList.Add(ShortestDistptr); // Go to next node

		DrawDebugLine(GetWorld(),CurrentVert->GetActorLocation(),
		 	CurrentVert->EdgeList[0]->GetActorLocation(),FColor::Green,
		 	true,-1,0,3); // Draw line path
		
		CurrentVert = CurrentVert->EdgeList[0];
	}
	CurrentVert->EdgeList.Add(Start); // Complete the loop

	DrawDebugLine(GetWorld(),CurrentVert->GetActorLocation(),
			 CurrentVert->EdgeList[0]->GetActorLocation(),FColor::Green,
			 true,-1,0,3);

	Start->PreviousVert = CurrentVert;
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
	//VertList[18]->EdgeList = EndVert;
	
	StartVert->Distance = 0;
	StartVert->bVisited = true;
	//StartVert->PreviousVert = nullptr;
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
	 			TotalDistance = CurrentVert->EdgeList[i]->Distance + CurrentVert->Distance;
	
	 			Unvisited.Emplace(CurrentVert->EdgeList[i]->Distance, CurrentVert->EdgeList[i]);
	
	 			if (TotalDistance < CurrentVert->EdgeList[i]->Distance) {
	 				CurrentVert->EdgeList[i]->Distance = TotalDistance;
	 				CurrentVert->EdgeList[i]->PreviousVert = CurrentVert;
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
