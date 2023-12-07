// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServerSession.h"
#include "GameService.h"
#include "NetSocket.generated.h"

enum Packet_C2P
{
{%- for pkt in parser.total_pkt %}
	{{pkt.name}} = {{pkt.id}},
{%- endfor %}
};

{%- for pkt in parser.total_pkt %}
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FDEL_{{pkt.name}}, PacketSessionRef&, BYTE*, int32);
{%- endfor %}

UCLASS()
class CLIENT_API ANetSocket : public AActor
{
	GENERATED_BODY()

{%- for pkt in parser.total_pkt %}
	FDEL_{{pkt.name}} {{pkt.name}}_dele;
{%- endfor %}

public:
	// Sets default values for this actor's properties
	ANetSocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateService();
	bool NetSocketPacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len);

private:
	bool IsConnected = false;
	std::shared_ptr<GameService> _service;

	//RecvPacket
private:
	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
{%- for pkt in parser.recv_pkt %}
	bool {{pkt.name}}_Process(PacketSessionRef& session, BYTE* buffer, int32 len);
{% endfor %}
	//Send
public:
	template<typename T>
	void Send(T& packet, uint16 col);

private:
	template<typename T>
	SendBufferRef MakeSendBuffer(T& packet, uint16 pktId);
};

template<typename T>
inline void ANetSocket::Send(T& packet, uint16 col)
{
	SendBufferRef buffer = MakeSendBuffer(packet, col);
	_service->Send(buffer);
}

template<typename T>
inline SendBufferRef ANetSocket::MakeSendBuffer(T& packet, uint16 pktId)
{
	const uint16 dataSize = static_cast<uint16>(packet.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	SendBufferRef sendBuffer = make_shared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->size = packetSize;
	header->id = pktId;
	packet.SerializeToArray(&header[1], dataSize);
	sendBuffer->Close(packetSize);

	return sendBuffer;
}
