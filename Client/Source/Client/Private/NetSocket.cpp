// Fill out your copyright notice in the Description page of Project Settings.


#include "NetSocket.h"
#include "NetWork/NetAddress.h"
#include "Kismet/GameplayStatics.h"

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

	//create service
	_service = make_shared<GameService>();
	_service->SetNetAddress(NetAddress("127.0.0.1", 7777));
	_service->SetSessionFactory(make_shared<ServerSession>);
	_service->SetCore(make_shared<NetCore>());
	_service->SetMaxSessionCount(1);
	_service->SetOwner(this);

	//service start
	if (_service->Start()) IsConnected = true;
}

/*
Recv Packet Process
*/

bool ANetSocket::NetSocketPacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	Packet_C2P protocol = (Packet_C2P)header->id;
	switch (protocol)
	{
	case P2C_ResultLogin:
		return P2C_ResultLogin_Process(session, buffer, len);
	case P2C_ReportMove:
		break;
	case P2C_ResultCollision:
		break;
	case P2C_ReportUpdateMonsters:
		break;
	case P2C_ReportEnterUser:
		return P2C_ReportEnterUser_Process(session, buffer, len);
		break;
	case P2C_ReportLeaveUser:
		return P2C_ReportLeaveUser_Process(session, buffer, len);
	default:
		return Handle_INVALID(session, buffer, len);
	}

	return false;
}

#pragma region  RecvPacketProcess

bool ANetSocket::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool ANetSocket::P2C_ResultLogin_Process(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ResultLogin packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return false;

	//delegate broadcast
	P2C_ResultLogin_dele.Broadcast(session, buffer, len);
	P2C_ResultLogin_dele_one.Broadcast();

	
	//process
	int aa = packet.result();

	return true;
}

bool ANetSocket::P2C_ReportEnterUser_Process(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ReportEnterUser packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return false;

	//delegate broadcast
	P2C_ReportEnterUser_dele.Broadcast(session, buffer, len);

	//process
	
	return true;
}

bool ANetSocket::P2C_ReportLeaveUser_Process(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ReportLeaveUser packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return false;

	//delegate broadcast
	P2C_ReportLeaveUser_dele.Broadcast(session, buffer, len);
	//process


	return true;
}

#pragma endregion


