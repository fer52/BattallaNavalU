// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeGridManager.h"

// Sets default values
ACubeGridManager::ACubeGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACubeGridManager::InitializeGrid()
{
    FVector StartLocation = GetActorLocation();
    float CubeSize = 100.0f; // Size of each cube

    for (int32 Row = 0; Row < GridSize; ++Row)
    {
        for (int32 Column = 0; Column < GridSize; ++Column)
        {
            FVector Location = StartLocation + FVector(Row * CubeSize, Column * CubeSize, 0);
            FActorSpawnParameters SpawnParams;
            CubeGrid[Row][Column] = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), Location, FRotator::ZeroRotator, SpawnParams);

            if (CubeGrid[Row][Column])
            {
                UStaticMeshComponent* MeshComp = CubeGrid[Row][Column]->GetStaticMeshComponent();
                if (MeshComp)
                {
                    MeshComp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube")).Object);
                }
            }
        }
    }
}

void ACubeGridManager::SetCubeColor(int32 Row, int32 Column, FLinearColor NewColor)
{
    if (Row >= 0 && Row < GridSize && Column >= 0 && Column < GridSize && CubeGrid[Row][Column])
    {
        UStaticMeshComponent* MeshComp = CubeGrid[Row][Column]->GetStaticMeshComponent();
        if (MeshComp)
        {
            UMaterialInstanceDynamic* DynMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
            if (DynMaterial)
            {
                DynMaterial->SetVectorParameterValue("BaseColor", NewColor);
            }
        }
    }
}

void ACubeGridManager::SetCubeMaterial(int32 Row, int32 Column, UMaterialInterface* NewMaterial)
{
    if (Row >= 0 && Row < GridSize && Column >= 0 && Column < GridSize && CubeGrid[Row][Column])
    {
        UStaticMeshComponent* MeshComp = CubeGrid[Row][Column]->GetStaticMeshComponent();
        if (MeshComp)
        {
            MeshComp->SetMaterial(0, NewMaterial);
        }
    }
}