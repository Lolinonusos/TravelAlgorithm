// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//#include "MyGraph.h"

#include "MyVertex.generated.h"


USTRUCT(BlueprintType)
struct FMyEdge {
	GENERATED_BODY()

	int source; // ?
	int dest; // index of destination vertex
	float weight; // Weight og travelling this edge
};



UCLASS()
class TRAVELALGORITHM_API AMyVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyVertex();

	int32 Weight;
	
	UPROPERTY()
	AMyVertex* Edge;

	UPROPERTY()
	AMyVertex* ReverseEdge;
	
	UPROPERTY()
	AMyVertex* PreviousVert;
	
	TArray<AMyVertex*> EdgeList; // Contains edges that point to other vertexes

	
	float Distance;
	
	bool bVisited = false;
	
	// Vertexes visualized
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* SphereMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* StartMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* UnvisitedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* VisitedMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* EndMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSartMat();
	void SetUnvisitedMat();
	void SetVisitedMat();
	void SetEndMat();
};


