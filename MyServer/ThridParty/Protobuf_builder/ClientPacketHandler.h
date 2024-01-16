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
	C2P_RequestPlayerAttack = 1008,
	P2C_ResultPlayerAttack = 1009,
	P2C_ReportPlayerAttack = 1010,
};

// Custom Handlers
namespace Handler
{
	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
	bool C2P_RequestLogin(PacketSessionRef& session, Protocol::C2P_RequestLogin& packet);
	bool C2P_RequestWorldData(PacketSessionRef& session, Protocol::C2P_RequestWorldData& packet);
	bool C2P_ReportMove(PacketSessionRef& session, Protocol::C2P_ReportMove& packet);
	bool C2P_RequestPlayerAttack(PacketSessionRef& session, Protocol::C2P_RequestPlayerAttack& packet);
}


class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handler::Handle_INVALID;
		GPacketHandler[C2P_RequestLogin] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C2P_RequestLogin>(Handler::C2P_RequestLogin, session, buffer, len); };
		GPacketHandler[C2P_RequestWorldData] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C2P_RequestWorldData>(Handler::C2P_RequestWorldData, session, buffer, len); };
		GPacketHandler[C2P_ReportMove] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C2P_ReportMove>(Handler::C2P_ReportMove, session, buffer, len); };
		GPacketHandler[C2P_RequestPlayerAttack] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C2P_RequestPlayerAttack>(Handler::C2P_RequestPlayerAttack, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ResultLogin& packet) { return MakeSendBuffer(packet, P2C_ResultLogin); }
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ResultWorldData& packet) { return MakeSendBuffer(packet, P2C_ResultWorldData); }
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ReportEnterUser& packet) { return MakeSendBuffer(packet, P2C_ReportEnterUser); }
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ReportLeaveUser& packet) { return MakeSendBuffer(packet, P2C_ReportLeaveUser); }
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ReportMove& packet) { return MakeSendBuffer(packet, P2C_ReportMove); }
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ResultPlayerAttack& packet) { return MakeSendBuffer(packet, P2C_ResultPlayerAttack); }
	static SendBufferRef MakeSendBuffer(Protocol::P2C_ReportPlayerAttack& packet) { return MakeSendBuffer(packet, P2C_ReportPlayerAttack); }


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