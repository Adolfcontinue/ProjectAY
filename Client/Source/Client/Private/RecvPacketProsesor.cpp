// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvPacketProsesor.h"
#include "NetWork/NetSession.h"
#include "Protobuf/Struct.pb.h"
#include "Protobuf/Enum.pb.h"
#include "Protobuf/Protocol.pb.h"
#include "NetworkSocket.h"
#include "PreLoder.h"
#include "Kismet/GameplayStatics.h"
#include "AYGameState.h"
#include "../AYGameInstance.h"

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
	Handler[EPacket_C2P_Protocol::P2C_ResultLogin] = &URecvPacketProsesor::Proc_P2C_ResultLogin;
	Handler[EPacket_C2P_Protocol::P2C_ResultWorldData] = &URecvPacketProsesor::Proc_P2C_ResultWorldData;
	Handler[EPacket_C2P_Protocol::P2C_ReportEnterUser] = &URecvPacketProsesor::Proc_P2C_ReportEnterUser;
	Handler[EPacket_C2P_Protocol::P2C_ReportLeaveUser] = &URecvPacketProsesor::Proc_P2C_ReportLeaveUser;
	Handler[EPacket_C2P_Protocol::P2C_ReportMove] = &URecvPacketProsesor::Proc_P2C_ReportMove;
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

void URecvPacketProsesor::Proc_P2C_ResultLogin(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ResultLogin packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Delegate_P2C_Result.Broadcast();
}

void URecvPacketProsesor::Proc_P2C_ResultWorldData(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ResultWorldData packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	for (size_t i = 0; i < packet.users_size(); i++)
		GameInstance->AddPlayer(packet.users(i));
}

void URecvPacketProsesor::Proc_P2C_ReportEnterUser(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ReportEnterUser packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;
	
	//process
	GameInstance->AddPlayer(packet.user());
}

void URecvPacketProsesor::Proc_P2C_ReportLeaveUser(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ReportLeaveUser packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	GameInstance->RemovePlayer(packet.userkey());
}

void URecvPacketProsesor::Proc_P2C_ReportMove(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ReportMove packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	FVector pos;
	pos.Set(packet.posdata().posision().x(), packet.posdata().posision().y(), packet.posdata().posision().z());
	FQuat quat;
	quat.X = packet.posdata().rotation().x();
	quat.Y = packet.posdata().rotation().y();
	quat.Z = packet.posdata().rotation().z();
	quat.W = packet.posdata().rotation().w();
	GameInstance->RepPlayerMove(packet.userkey(), pos, quat);
}

