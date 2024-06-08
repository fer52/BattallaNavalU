// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "DatabaseManager.generated.h"

UCLASS()
class JUEGOBN_API ADatabaseManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADatabaseManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to execute SELECT query
    UFUNCTION(BlueprintCallable, Category = "Database")
    void ExecuteSelectQuery(FString MacAddress);

private:
    sql::Driver* Driver;
    sql::Connection* Connection;
    sql::Statement* Statement;

    void ConnectToDatabase();
};
