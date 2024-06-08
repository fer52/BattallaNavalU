// Fill out your copyright notice in the Description page of Project Settings.


#include "DatabaseManager.h"

// Sets default values
ADatabaseManager::ADatabaseManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADatabaseManager::BeginPlay()
{
	Super::BeginPlay();
	ConnectToDatabase();
	
}

// Called every frame
void ADatabaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADatabaseManager::ConnectToDatabase()
{
    try
    {
        Driver = get_driver_instance();
        Connection = Driver->connect("tcp://localhost:3306", "ferwc", "password_juego");
        Connection->setSchema("your_database_name");
        Statement = Connection->createStatement();
    }
    catch (sql::SQLException& e)
    {
        UE_LOG(LogTemp, Error, TEXT("MySQL connection error: %s"), UTF8_TO_TCHAR(e.what()));
    }
}

void ADatabaseManager::ExecuteSelectQuery(FString MacAddress)
{
    if (!Statement) return;

    try
    {
        std::string Query = "SELECT * FROM game WHERE ID = '" + std::string(TCHAR_TO_UTF8(*MacAddress)) + "'";
        sql::ResultSet* ResultSet = Statement->executeQuery(Query);

        while (ResultSet->next())
        {
            FString GameData = UTF8_TO_TCHAR(ResultSet->getString("game_column_name").c_str());
            UE_LOG(LogTemp, Log, TEXT("Game Data: %s"), *GameData);
        }

        delete ResultSet;
    }
    catch (sql::SQLException& e)
    {
        UE_LOG(LogTemp, Error, TEXT("MySQL query error: %s"), UTF8_TO_TCHAR(e.what()));
    }
}
