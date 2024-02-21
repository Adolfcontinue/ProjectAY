// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Public/NetworkSocket.h"
#include "Public/RecvPacketProsesor.h"
#include "Public/Protobuf/Enum.pb.h"
#include "Public/Protobuf/Struct.pb.h"
#include "Public/Protobuf/Protocol.pb.h"
#include "Public/Define.h"
#include "AYGameInstance.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_TwoParams(handlerz, int, int);

UCLASS()
class CLIENT_API UAYGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	virtual void Init();
	virtual void Shutdown();

public:
	NetworkSocket* GetNetworkSocket();
	URecvPacketProsesor* GetRecvProsessor();
	void RecvPacketPush(BYTE* buffer, int32 len);

private:
	NetworkSocket* Socket;
	URecvPacketProsesor* RecvProsesor;
	class UTableManager* TableManager;

public:
	void AddPlayer(Protocol::UserData userData);
	void RemovePlayer(int64 userKey);
	void AddMonster(Protocol::MonsterData monsterData);

	void RepPlayerMove(int64 userKey, FVector pos, float yaw, Protocol::ActorState state);
	void RepPlayerAttack(int64 victimKey, double damageAmount);
	void RepMonsterState(int64 actorKey, FVector pos, Protocol::ActorState state);
	void RepMonsterState(int64 actorKey, FVector pos, FVector targetPos, Protocol::ActorState state);
	
public:
	template<typename T>
	void Send(T& packet, uint16 col);
};

template<typename T>
inline void UAYGameInstance::Send(T& packet, uint16 col)
{
	if (Socket)
		Socket->Send(packet, col);
}
