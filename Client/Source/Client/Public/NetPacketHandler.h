// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
//extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

//
//namespace Handler
//{
//	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
//	bool P2C_ResultLogin(PacketSessionRef& session, Protocol::P2C_ResultLogin& packet);
//	bool P2C_ReportMove(PacketSessionRef& session, Protocol::P2C_ReportMove& packet);
//	bool P2C_ResultCollision(PacketSessionRef& session, Protocol::P2C_ResultCollision& packet);
//	bool P2C_ReportUpdateMonsters(PacketSessionRef& session, Protocol::P2C_ReportUpdateMonsters& packet);
//}
//
//class CLIENT_API NetPacketHandler
//{
//public:
//	static void Init()
//	{
//		for (int32 i = 0; i < UINT16_MAX; i++)
//			GPacketHandler[i] = Handler::Handle_INVALID;
//		GPacketHandler[P2C_ResultLogin] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ResultLogin>(Handler::P2C_ResultLogin, session, buffer, len); };
//		GPacketHandler[P2C_ReportMove] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ReportMove>(Handler::P2C_ReportMove, session, buffer, len); };
//		GPacketHandler[P2C_ResultCollision] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ResultCollision>(Handler::P2C_ResultCollision, session, buffer, len); };
//		GPacketHandler[P2C_ReportUpdateMonsters] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ReportUpdateMonsters>(Handler::P2C_ReportUpdateMonsters, session, buffer, len); };
//	}
//
//	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
//	{
//		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
//		return GPacketHandler[header->id](session, buffer, len);
//	}
//
//public:
//	static SendBufferRef MakeSendBuffer(Protocol::C2P_RequestLogin& packet) { return MakeSendBuffer(packet, C2P_RequestLogin); }
//
//
//private:
//	template<typename PacketType, typename ProcessFunc>
//	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
//	{
//		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
//		return GPacketHandler[header->id](session, buffer, len);
//	}
//
//
//private:
//	template<typename PacketType, typename ProcessFunc>
//	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
//	{
//		PacketType pkt;
//		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
//			return false;
//
//		return func(session, pkt);
//	}
//	template<typename T>
//	static SendBufferRef MakeSendBuffer(T& packet, uint16 pktId)
//	{
//		const uint16 dataSize = static_cast<uint16>(packet.ByteSizeLong());
//		const uint16 packetSize = dataSize + sizeof(PacketHeader);
//
//		SendBufferRef sendBuffer = make_shared<SendBuffer>(packetSize);
//		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
//		header->size = packetSize;
//		header->id = pktId;
//		packet.SerializeToArray(&header[1], dataSize);
//		sendBuffer->Close(packetSize);
//
//		return sendBuffer;
//	}
//};
