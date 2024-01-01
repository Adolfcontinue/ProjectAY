#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum Packet_C2P
{
	C2P_RequestLogin = 1000,
	P2C_ResultLogin = 1001,
	C2P_RequestWorldData = 1002,
	P2C_ResultWorldData = 1003,
};

// Custom Handlers
namespace Handler
{
	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
	bool P2C_ResultLogin(PacketSessionRef& session, Protocol::P2C_ResultLogin& packet);
	bool P2C_ResultWorldData(PacketSessionRef& session, Protocol::P2C_ResultWorldData& packet);
}


class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handler::Handle_INVALID;
		GPacketHandler[P2C_ResultLogin] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ResultLogin>(Handler::P2C_ResultLogin, session, buffer, len); };
		GPacketHandler[P2C_ResultWorldData] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ResultWorldData>(Handler::P2C_ResultWorldData, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::C2P_RequestLogin& packet) { return MakeSendBuffer(packet, C2P_RequestLogin); }
	static SendBufferRef MakeSendBuffer(Protocol::C2P_RequestWorldData& packet) { return MakeSendBuffer(packet, C2P_RequestWorldData); }


private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType packet;
		if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, packet);
	}

	template<typename T>
	static SendBufferRef MakeSendBuffer(T& packet, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(packet.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = SendBufferManager::Instance().Open(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(packet.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};