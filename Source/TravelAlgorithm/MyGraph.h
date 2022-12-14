// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MyVertex.h"

#include "MyGraph.generated.h"

UCLASS()
class TRAVELALGORITHM_API AMyGraph : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyGraph();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This is for spawning the blueprint versions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vertex")
	TSubclassOf<AMyVertex> BP_Vertex;

	
	UPROPERTY(VisibleAnywhere, Category = "Vertex")
	TArray<AMyVertex*> VertList; // Hold all the nodes

	// Find the cheapest path
	UPROPERTY()
	AMyVertex* Cheapest;
	

	UFUNCTION()
	void EdgeSetup();

	// Part of Travelling Salesman
	UFUNCTION(BlueprintCallable)
	void TSP(AMyVertex* Start);
	
	// Part of Dijkstra
	UFUNCTION(BlueprintCallable)
	void Dijkstra(AMyVertex* Start, AMyVertex* End);

	// Part of A*
	UFUNCTION(BlueprintCallable)
	void AStar(AMyVertex* Start, AMyVertex* End);
	
	UFUNCTION(BlueprintCallable)
	void DeleteGraph();
};
