// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameService.h"
#include "ServerSession.h"
#include "Network/SendBuffer.h"
#include "HAL/Runnable.h"
/**
 * 
 */
enum EPacket_C2P_Protocol
{
	C2P_RequestLogin = 1000,
	P2C_ResultLogin = 1001,
	C2P_RequestWorldData = 1002,
	P2C_ResultWorldData = 1003,
	P2C_ReportEnterUser = 1004,
	P2C_ReportLeaveUser = 1005,
	C2P_ReportMove = 1006,
	P2C_ReportMove = 1007,
	C2P_RequestPlayerAttack = 1008,
	P2C_ResultPlayerAttack = 1009,
	P2C_ReportPlayerAttack = 1010,
	P2C_ReportMonsterState = 1011,
};

class CLIENT_API NetworkSocket : public FRunnable
{
public:
	NetworkSocket();
	~NetworkSocket();
	
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;


private:
	void CreateStartService();
	void ServiceRun(uint32 time);

public:
	void NetworkClose();

public:
	bool NetSocketPacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len);
	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
	void SetGameInstance(class UAYGameInstance* inst);
	class UAYGameInstance* GetGameInstance();

private:
	bool IsConnected;
	std::shared_ptr<GameService> Service;
	class UAYGameInstance* GameInstance;


public:
	template<typename T>
	void Send(T& packet, uint16 col);

private:
	template<typename T>
	SendBufferRef MakeSendBuffer(T& packet, uint16 col);
};

template<typename T>
inline void NetworkSocket::Send(T& packet, uint16 col)
{
	SendBufferRef buffer = MakeSendBuffer(packet, col);
	Service->Send(buffer);
}

template<typename T>
inline SendBufferRef NetworkSocket::MakeSendBuffer(T& packet, uint16 col)
{
	const uint16 dataSize = static_cast<uint16>(packet.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	SendBufferRef sendBuffer = make_shared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->size = packetSize;
	header->id = col;
	packet.SerializeToArray(&header[1], dataSize);
	sendBuffer->Close(packetSize);

	return sendBuffer;
}
