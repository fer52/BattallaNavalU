// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeGridManager.generated.h"

UCLASS()
class JUEGOBN_API ACubeGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Method to initialize the grid
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void InitializeGrid();

	// Method to set the color of a specific cube
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetCubeColor(int32 Row, int32 Column, FLinearColor NewColor);

	// Method to set the material of a specific cube
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetCubeMaterial(int32 Row, int32 Column, UMaterialInterface* NewMaterial);

private:
	// The size of the grid
	static const int32 GridSize = 5;

	// Array to store the cube actors
	AStaticMeshActor* CubeGrid[GridSize][GridSize];

};
