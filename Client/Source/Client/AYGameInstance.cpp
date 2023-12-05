// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameInstance.h"
#include "NetWork/NetSocketUtils.h"
#include "NetPacketHandler.h"

void UAYGameInstance::Init()
{
	Super::Init();

	//server connect init
	NetSocketUtils::Init();

	//create server socket actor
	ANetSocket* SpawnedActor1 = (ANetSocket*)GetWorld()->SpawnActor(ANetSocket::StaticClass());
	SpawnedActor1->CreateService();
	_socket = SpawnedActor1;
}

