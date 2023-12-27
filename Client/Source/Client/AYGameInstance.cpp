// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameInstance.h"
#include "NetWork/NetSocketUtils.h"
#include "NetPacketHandler.h"

void UAYGameInstance::Init()
{
	Super::Init();

	NetSocketUtils::Init();
	Socket = new NetworkSocket();
	Socket->SetGameInstance(this);
	FRunnableThread::Create(Socket, TEXT("network_thread"));
	RecvProsesor = NewObject<URecvPacketProsesor>();
	RecvProsesor->Init();
}

NetworkSocket* UAYGameInstance::GetNetworkSocket()
{
	if (Socket == nullptr)
		return nullptr;

	return Socket;
}

URecvPacketProsesor* UAYGameInstance::GetRecvProsessor()
{
	return RecvProsesor;
}

void UAYGameInstance::RecvPacketPush(BYTE* buffer, int32 len)
{
	RecvProsesor->Push(buffer, len);
}

