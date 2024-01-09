// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkSocket.h"
#include "ServerSession.h"
#include "../AYGameInstance.h"
#include "PreLoder.h"

NetworkSocket::NetworkSocket()
{
	IsConnected = false;
}

NetworkSocket::~NetworkSocket()
{
	LOG("~NetworkSocket");
}

bool NetworkSocket::Init()
{
	CreateStartService();
	return true;
}

uint32 NetworkSocket::Run()
{
	while (IsConnected)
	{
		ServiceRun(10);
	}
	return 1;
}

void NetworkSocket::Stop()
{
	IsConnected = false;

	Service->GetSession()->Disconnect(L"DisConnect");
}

void NetworkSocket::Exit()
{
}

void NetworkSocket::CreateStartService()
{
	if (IsConnected)
		return;

	//create service
	Service = make_shared<GameService>();
	Service->SetNetAddress(NetAddress("127.0.0.1", 7777));
	Service->SetSessionFactory(make_shared<ServerSession>);
	Service->SetCore(make_shared<NetCore>());
	Service->SetMaxSessionCount(1);
	Service->SetOwner(this);

	//service start
	if (Service->Start()) IsConnected = true;
}

void NetworkSocket::ServiceRun(uint32 time)
{
	if(IsConnected)
		Service->GetCore()->Dispatch(time);
}

bool NetworkSocket::NetSocketPacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	GameInstance->RecvPacketPush(buffer, len);
	return true;
}

bool NetworkSocket::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

void NetworkSocket::SetGameInstance(UAYGameInstance* inst)
{
	GameInstance = inst;
}

UAYGameInstance* NetworkSocket::GetGameInstance()
{
	return GameInstance;
}
