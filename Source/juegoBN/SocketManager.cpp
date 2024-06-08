// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketManager.h"

// Sets default values
ASocketManager::ASocketManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Socket = nullptr;
	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

}

// Called when the game starts or when spawned
void ASocketManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASocketManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ASocketManager::InitializeSocket()
{
    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("default"), false);
    return Socket != nullptr;
}

bool ASocketManager::ConnectToServer(FString ServerAddress, int32 ServerPort)
{
    if (!InitializeSocket()) return false;

    TSharedPtr<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
    bool bIsValid;
    Addr->SetIp(*ServerAddress, bIsValid);
    Addr->SetPort(ServerPort);

    if (bIsValid)
    {
        return Socket->Connect(*Addr);
    }

    return false;
}

void ASocketManager::SendData(FString Message)
{
    if (!Socket) return;

    // Convert FString to char array
    TCHAR* SerializedChar = Message.GetCharArray().GetData();
    int32 Size = FCString::Strlen(SerializedChar);
    int32 Sent = 0;

    // Send the data over the socket
    Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);
}

void ASocketManager::Disconnect()
{
    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
}