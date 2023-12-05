// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameInstance.h"
#include "NetWork/NetSocketUtils.h"
#include "NetPacketHandler.h"

void UAYGameInstance::Init()
{
	Super::Init();
	NetPacketHandler::Init();

	NetSocketUtils::Init();
	ANetSocket* SpawnedActor1 = (ANetSocket*)GetWorld()->SpawnActor(ANetSocket::StaticClass());
	SpawnedActor1->CreateService();
}
