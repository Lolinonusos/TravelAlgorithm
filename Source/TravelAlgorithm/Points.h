// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Points.generated.h"

USTRUCT(BlueprintType)
struct FInnerMatrixStruct {
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<int32> InnerMatrix;
};

USTRUCT()
struct FVertex {
	GENERATED_BODY()

	int32 Value = 0; 
	bool Visited;
};

USTRUCT()
struct FGraph {
	GENERATED_BODY()
	
};

UCLASS()
class TRAVELALGORITHM_API APoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoints();

	// Vertexes visualized
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* SphereMesh;
	
	int32 VertexAmount = 5;
	
	UPROPERTY()
	TArray<FInnerMatrixStruct> AdjacencyMatrix;
	
	UPROPERTY()
	APoints* StartPoint;

	UPROPERTY()
	APoints* EndPoint;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* StartMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* UnvisitedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* VisitedMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterial* EndMaterial;
	
	//std::list<std::pair<int, int>>* adj; // these are the connecting vertexes
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MatrixSetup();

	UFUNCTION()
	void EdgeSetup();
	
	UFUNCTION()
	void Dijkstra();


	
};
