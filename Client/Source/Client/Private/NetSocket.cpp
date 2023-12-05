// Fill out your copyright notice in the Description page of Project Settings.


#include "NetSocket.h"
#include "NetWork/NetAddress.h"
#include "ServerSession.h"

// Sets default values
ANetSocket::ANetSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetSocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsConnected)
		return;

	_service->GetCore()->Dispatch(10);

}

void ANetSocket::CreateService()
{
	if (IsConnected)
		return;

	_service = make_shared<ClientService>();
	_service->SetNetAddress(NetAddress("127.0.0.1", 7777));
	_service->SetSessionFactory(make_shared<ServerSession>);
	_service->SetCore(make_shared<NetCore>());
	_service->SetMaxSessionCount(1);

	if (_service->Start()) IsConnected = true;
	
}

