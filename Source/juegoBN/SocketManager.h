// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "SocketManager.generated.h"

UCLASS()
class JUEGOBN_API ASocketManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocketManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to send data over the socket
    UFUNCTION(BlueprintCallable, Category = "Socket")
    void SendData(FString Message);

    // Function to connect the socket
    UFUNCTION(BlueprintCallable, Category = "Socket")
    bool ConnectToServer(FString ServerAddress, int32 ServerPort);

    // Function to disconnect the socket
    UFUNCTION(BlueprintCallable, Category = "Socket")
    void Disconnect();

private:
    FSocket* Socket;
    ISocketSubsystem* SocketSubsystem;

    bool InitializeSocket();
};
