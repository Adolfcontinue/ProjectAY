// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvPacketProsesor.h"
#include "NetWork/NetSession.h"
#include "Enum.pb.h"
#include "Protocol.pb.h"
#include "Struct.pb.h"
#include "NetworkSocket.h"
#include "PreLoder.h"

void URecvPacketProsesor::CallTimer()
{
	FTimerHandle tHandle;
	const float Delay = 1.0f;
	//GetWorld()->GetTimerManager().SetTimer(tHandle, this, &URecvPacketProsesor::TestTimer, Delay, false);
}

void URecvPacketProsesor::TestTimer()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Hello World");
}

void URecvPacketProsesor::Init()
{
	Handler[EPacket_C2P_Protocol::P2C_ResultLogin] = &URecvPacketProsesor::Result_P2C_ResultLogin;
	Handler[EPacket_C2P_Protocol::P2C_ResultWorldData] = &URecvPacketProsesor::Result_P2C_ResultWorldData;
	//Handler.Add(EPacket_C2P_Protocol::P2C_ResultLogin, &URecvPacketProsesor::Result_P2C_ResultLogin);

}

void URecvPacketProsesor::Tick(float DeltaTime)
{
	if (!RecvQueue.IsEmpty())
	{
		RecvPacket* packet = RecvQueue.Peek();
		PacketHandle((*packet).Buffer, (*packet).Len);
		RecvQueue.Pop();
	}
}

bool URecvPacketProsesor::IsTickable() const
{
	return true;
}

bool URecvPacketProsesor::IsTickableInEditor() const
{
	return true;
}

bool URecvPacketProsesor::IsTickableWhenPaused() const
{
	return false;
}

TStatId URecvPacketProsesor::GetStatId() const
{
	return TStatId();
}

void URecvPacketProsesor::Push(RecvPacket packet)
{
	RecvQueue.Enqueue(packet);
}

void URecvPacketProsesor::Push(BYTE* buffer, int32 len)
{
	RecvQueue.Enqueue(RecvPacket(buffer, len));
}

void URecvPacketProsesor::SetGameInstance(UAYGameInstance* instance)
{
	GameInstance = instance;
}

UAYGameInstance* URecvPacketProsesor::GetGameInstance()
{
	return GameInstance;
}

void URecvPacketProsesor::PacketHandle(BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	EPacket_C2P_Protocol protocol = (EPacket_C2P_Protocol)header->id;
	auto iter = Handler.find(protocol);
	if (iter == Handler.end())
		return;

	Handler[protocol](*this, buffer, len);
}

void URecvPacketProsesor::Result_P2C_ResultLogin(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ResultLogin packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Delegate_P2C_Result.Broadcast();

	LOG_SCREEN(FColor::Blue,"Result_P2C_ResultLogin");
}

void URecvPacketProsesor::Result_P2C_ResultWorldData(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ResultWorldData packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	LOG_SCREEN(FColor::Blue, "Result_P2C_ResultWorldData");
}

