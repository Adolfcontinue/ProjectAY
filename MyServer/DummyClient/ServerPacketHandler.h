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
	P2C_ReportEnterUser = 1004,
	P2C_ReportLeaveUser = 1005,
	C2P_ReportMove = 1006,
	P2C_ReportMove = 1007,
	C2P_ReportAnimSync = 1008,
	P2C_ReportAnimSync = 1009,
};

// Custom Handlers
namespace Handler
{
	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
	bool P2C_ResultLogin(PacketSessionRef& session, Protocol::P2C_ResultLogin& packet);
	bool P2C_ResultWorldData(PacketSessionRef& session, Protocol::P2C_ResultWorldData& packet);
	bool P2C_ReportEnterUser(PacketSessionRef& session, Protocol::P2C_ReportEnterUser& packet);
	bool P2C_ReportLeaveUser(PacketSessionRef& session, Protocol::P2C_ReportLeaveUser& packet);
	bool P2C_ReportMove(PacketSessionRef& session, Protocol::P2C_ReportMove& packet);
	bool P2C_ReportAnimSync(PacketSessionRef& session, Protocol::P2C_ReportAnimSync& packet);
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
		GPacketHandler[P2C_ReportEnterUser] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ReportEnterUser>(Handler::P2C_ReportEnterUser, session, buffer, len); };
		GPacketHandler[P2C_ReportLeaveUser] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ReportLeaveUser>(Handler::P2C_ReportLeaveUser, session, buffer, len); };
		GPacketHandler[P2C_ReportMove] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ReportMove>(Handler::P2C_ReportMove, session, buffer, len); };
		GPacketHandler[P2C_ReportAnimSync] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::P2C_ReportAnimSync>(Handler::P2C_ReportAnimSync, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::C2P_RequestLogin& packet) { return MakeSendBuffer(packet, C2P_RequestLogin); }
	static SendBufferRef MakeSendBuffer(Protocol::C2P_RequestWorldData& packet) { return MakeSendBuffer(packet, C2P_RequestWorldData); }
	static SendBufferRef MakeSendBuffer(Protocol::C2P_ReportMove& packet) { return MakeSendBuffer(packet, C2P_ReportMove); }
	static SendBufferRef MakeSendBuffer(Protocol::C2P_ReportAnimSync& packet) { return MakeSendBuffer(packet, C2P_ReportAnimSync); }


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