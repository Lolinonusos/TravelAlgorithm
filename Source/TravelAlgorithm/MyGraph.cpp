// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGraph.h"

//#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"


// Sets default values
AMyGraph::AMyGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}


// Called when the game starts or when spawned
void AMyGraph::BeginPlay() {
	Super::BeginPlay();
	
	int32 VertexTotal = 50;
	
	UWorld* World = GetWorld();
	if (World)
	{
		{
			for (int i = 0; i < VertexTotal; i++) {
				AMyVertex* NewVertex = World->SpawnActor<AMyVertex>(BP_Vertex,
					FVector(FMath::RandRange(-1000.0f,1000.0f),FMath::RandRange(-1000.0f,1000.0f), FMath::RandRange(0.0f,1000.0f)),
					FRotator(0.0f, 0.0f, 0.0f));
				// UE_LOG(LogTemp, Warning, TEXT("Hello %d"), i);
				if (NewVertex) {
					VertList.Add(NewVertex);
					// if (i == 0) {
					// 	VertList[i]->SetSartMat();
					// }
					// if (i == VertexTotal - 1) {
					// 	VertList[i]->SetEndMat();
					// }
					VertList[i]->SetUnvisitedMat();
				}
			}
		}
		//TSP(VertList[0]);

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
	for (AMyVertex* Vert : VertList) { // Different way of for looping: for (*Datatype of Array* newName : Array)

		int RandEdgeAmount = FMath::RandRange(2,6);

		for (int i = 0; i < RandEdgeAmount; i++) {
			int RandVert = FMath::RandRange(0,VertList.Num() - 1);
			
			Vert->EdgeList.Emplace(VertList[RandVert]); // Connect Vert to random vert
			VertList[RandVert]->EdgeList.Emplace(Vert); // Connect randomvert back the current vert
			DrawDebugLine(GetWorld(), Vert->GetActorLocation(), VertList[RandVert]->GetActorLocation(),
				FColor::White,true, -1, 0, 1); // draw line between the vertices
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
	//FTimerHandle TimerHandle;
	
	while (!allVisited) {

        //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyGraph::TSP, 1.f, true);

		CurrentVert->bVisited = true;
		float ShortestDist = 99999;
		int visitedCounter = 0;
		
		for(int i = 0; i < UnvisitedArr.Num(); i++) {

			float VertDistance = FVector::Distance(CurrentVert->GetActorLocation(), UnvisitedArr[i]->GetActorLocation());

			if (ShortestDist > VertDistance && UnvisitedArr[i]->bVisited == false) {
				ShortestDist = VertDistance;
				ShortestDistptr = UnvisitedArr[i];
			}
			
			if (UnvisitedArr[i]->bVisited) {
				visitedCounter += 1;
				if (visitedCounter == UnvisitedArr.Num() - 1) {
					allVisited = true;
				}
			}
		}
		CurrentVert->EdgeList.Add(ShortestDistptr); // Add pointer to next vertex

		DrawDebugLine(GetWorld(),CurrentVert->GetActorLocation(),
		 	CurrentVert->EdgeList[0]->GetActorLocation(),FColor::Green,
		 	true,-1,0,3); // Draw line path
		
		CurrentVert = CurrentVert->EdgeList[0]; // Go to next vertex
	}
	CurrentVert->EdgeList.Add(Start); // Add pointer from last node to start

	DrawDebugLine(GetWorld(),CurrentVert->GetActorLocation(),
			 CurrentVert->EdgeList[0]->GetActorLocation(),FColor::Red,
			 true,-1,0,3);

	CurrentVert = CurrentVert->EdgeList[0];
}

void AMyGraph::Dijkstra(AMyVertex* StartVert, AMyVertex* EndVert) {

	//TQueue<int> Q;
	//TMap<float, float> Visited = {};
	TMap<float, AMyVertex*> UnvisitedMap;

	
	for (int i = 0; i < VertList.Num(); i++) {
		
		if (VertList[i] != StartVert) {
			VertList[i]->Distance = 99999;// Infinity
			VertList[i]->bVisited = false;
			VertList[i]->PreviousVert = nullptr;
			//Unvisited.Emplace(VertList[i]->Distance, VertList[i]); 
		}
	}
	
	StartVert->Distance = 0;
	StartVert->bVisited = true;
	StartVert->PreviousVert = nullptr;
	StartVert->SetSartMat();
	AMyVertex* CurrentVert = StartVert;
	EndVert->Distance = 0;
	
	// if (StartVert == nullptr) {
	// 	return;
	// }
	// if (EndVert == nullptr) {
	// 	return;
	// }
	
	
		
	//if (CurrentVert) {
		
		while (!EndVert->bVisited) {

			UE_LOG(LogTemp, Warning, TEXT("There are %d"), UnvisitedMap.Num());

			// Check for neighbours
	 		for (int i = 0; i < CurrentVert->EdgeList.Num(); i++) {
	 			// Only execute if neighbour vertex is not visited
	 			if (!CurrentVert->EdgeList[i]->bVisited) { 

					float DistanceBetweenVerts = CurrentVert->GetDistanceTo(CurrentVert->EdgeList[i]);
	 				
	 				float TotalDistance = DistanceBetweenVerts + CurrentVert->Distance;
		
					CurrentVert->EdgeList[i]->PreviousVert = CurrentVert;
		
	 				if (TotalDistance < CurrentVert->EdgeList[i]->Distance) {
	 					
	 					CurrentVert->EdgeList[i]->Distance = TotalDistance;
	 					UE_LOG(LogTemp, Warning, TEXT("Setting previous"));

	 				}
	 				
	 				UnvisitedMap.Emplace(CurrentVert->EdgeList[i]->Distance, CurrentVert->EdgeList[i]);
	 				UE_LOG(LogTemp, Warning, TEXT("Emplacing into TMap"));

	 			}
	 		}
		
	 		if (UnvisitedMap.begin().Value()->bVisited == false) {
	 			UnvisitedMap.KeySort([](float A, float B) {return A < B;});
	 			Cheapest = UnvisitedMap.begin().Value();
	 			//Unvisited.begin().Value()->PreviousVert = CurrentVert;

	 			if (Cheapest) {
	 				
	 			DrawDebugLine(GetWorld(),CurrentVert->GetActorLocation(),Cheapest->GetActorLocation(),
					 FColor::Blue,true,-1,0,5);
	 			}
	 			//Cheapest->PreviousVert = CurrentVert;
	 			
	 			CurrentVert = Cheapest;
				CurrentVert->SetVisitedMat();
	 			UnvisitedMap.Remove(UnvisitedMap.begin().Key());
	 		}
			CurrentVert->bVisited = true;


			
			if (EndVert->bVisited == true) {
	 			UE_LOG(LogTemp, Warning, TEXT("BIG SUCCESS"));
				EndVert->SetEndMat();
				//EndVert->PreviousVert = CurrentVert;
				if (CurrentVert == EndVert) {
					UE_LOG(LogTemp, Warning, TEXT("CurrentVert = Endvert"));
				}
	 		}

		}
		if (EndVert->PreviousVert == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Whydo"));

		}
		AMyVertex* DrawPath = EndVert;
		if (DrawPath->PreviousVert != nullptr) {
			while(DrawPath->PreviousVert != nullptr) {

				UE_LOG(LogTemp, Warning, TEXT("Help"));
				DrawDebugLine(GetWorld(),DrawPath->GetActorLocation(),DrawPath->PreviousVert->GetActorLocation(),
					FColor::Red,true,-1,0,5);
	 		
	 			DrawPath = DrawPath->PreviousVert;
			}
		}
		else {
		 	UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
	//}
	}


int AMyGraph::AStar() {

	
	return 1;
}

void AMyGraph::ReconstructPath() {
}

void AMyGraph::DeleteGraph() {

	for (int i = 0; i < VertList.Num(); i++) {
		VertList[i]->Destroy();
	}
	VertList.Empty();
}
