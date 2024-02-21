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
	Handler[EPacket_C2P_Protocol::P2C_ResultLogin] = &URecvPacketProsesor::P2C_ResultLogin;
	Handler[EPacket_C2P_Protocol::P2C_ResultWorldData] = &URecvPacketProsesor::P2C_ResultWorldData;
	Handler[EPacket_C2P_Protocol::P2C_ReportEnterUser] = &URecvPacketProsesor::P2C_ReportEnterUser;
	Handler[EPacket_C2P_Protocol::P2C_ReportLeaveUser] = &URecvPacketProsesor::P2C_ReportLeaveUser;
	Handler[EPacket_C2P_Protocol::P2C_ReportMove] = &URecvPacketProsesor::P2C_ReportMove;
	Handler[EPacket_C2P_Protocol::P2C_ReportPlayerAttack] = &URecvPacketProsesor::P2C_ReportPlayerAttack;
	Handler[EPacket_C2P_Protocol::P2C_ReportMonsterState] = &URecvPacketProsesor::P2C_ReportMonsterState;
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

void URecvPacketProsesor::P2C_ResultLogin(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ResultLogin packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Delegate_P2C_Result.Broadcast();
}

void URecvPacketProsesor::P2C_ResultWorldData(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ResultWorldData packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	for (size_t i = 0; i < packet.users_size(); i++)
		GameInstance->AddPlayer(packet.users(i));

	for (size_t i = 0; i < packet.monsters_size(); i++)
		GameInstance->AddMonster(packet.monsters(i));
}

void URecvPacketProsesor::P2C_ReportEnterUser(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ReportEnterUser packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;
	
	//process
	GameInstance->AddPlayer(packet.user());
}

void URecvPacketProsesor::P2C_ReportLeaveUser(BYTE* buffer, int32 len)
{
	//valid
	Protocol::P2C_ReportLeaveUser packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	GameInstance->RemovePlayer(packet.userkey());
}

void URecvPacketProsesor::P2C_ReportMove(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ReportMove packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	/*FVector pos;
	pos.Set(packet.posdata().posision().x(), packet.posdata().posision().y(), packet.posdata().posision().z());
	FQuat quat;
	quat.X = packet.posdata().rotation().x();
	quat.Y = packet.posdata().rotation().y();
	quat.Z = packet.posdata().rotation().z();
	quat.W = packet.posdata().rotation().w();*/

	FVector pos(packet.userdata().transform().x(), packet.userdata().transform().y(), packet.userdata().transform().z());
	float yaw = packet.userdata().transform().yaw();
	GameInstance->RepPlayerMove(packet.userdata().userkey(), pos, yaw, packet.userdata().state());
}

void URecvPacketProsesor::P2C_ReportPlayerAttack(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ReportPlayerAttack packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	GameInstance->RepPlayerAttack(packet.victimkey(), packet.damageamount());
}

void URecvPacketProsesor::P2C_ReportMonsterState(BYTE* buffer, int32 len)
{
	//vaild
	Protocol::P2C_ReportMonsterState packet;
	if (packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	//process
	FVector pos(packet.monster().transform().x(), packet.monster().transform().y(), packet.monster().transform().z());
	float yaw = packet.monster().transform().yaw();
	
	FVector target(packet.target().x(), packet.target().y(), packet.target().z());
	GameInstance->RepMonsterState(packet.actorkey(), pos, target, packet.monster().state());
	//GameInstance->RepMonsterState(packet.actorkey(), pos, packet.monster().state());
}

