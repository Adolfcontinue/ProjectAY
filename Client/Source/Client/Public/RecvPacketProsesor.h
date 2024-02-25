// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AYTickObject.h"
#include <functional>


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
	C2P_RequestMonsterAttack = 1012,
	P2C_ResultMonsterAttack = 1013,
};


DECLARE_MULTICAST_DELEGATE(FDEL_P2C_RESULT);
DECLARE_MULTICAST_DELEGATE_TwoParams(FDEL_P2C_REPORTMOVE, uint64, FVector);

struct RecvPacket
{
	RecvPacket() {}
	RecvPacket(BYTE* buffer, int32 len) : Buffer(buffer), Len(len) {}
	BYTE* Buffer;
	int32 Len;
};


class CLIENT_API URecvPacketProsesor : public FTickableGameObject
{

public:
	FDEL_P2C_RESULT Delegate_P2C_Result;
	FDEL_P2C_REPORTMOVE Delegate_P2C_ReportMove;

public:
	UFUNCTION(BlueprintCallable, Category = Test)
	void CallTimer();

	void TestTimer();
public:
	void Init();
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	
public:
	void Push(RecvPacket packet);
	void Push(BYTE* buffer, int32 len);

public:
	void SetGameInstance(class UAYGameInstance* instance);
	class UAYGameInstance* GetGameInstance();

private:
	void PacketHandle(BYTE* buffer, int32 len);
	void P2C_ResultLogin(BYTE* buffer, int32 len);
	void P2C_ResultWorldData(BYTE* buffer, int32 len);
	void P2C_ReportEnterUser(BYTE* buffer, int32 len);
	void P2C_ReportLeaveUser(BYTE* buffer, int32 len);
	void P2C_ReportMove(BYTE* buffer, int32 len);
	void P2C_ReportPlayerAttack(BYTE* buffer, int32 len);
	void P2C_ReportMonsterState(BYTE* buffer, int32 len);
	void P2C_ResultMonsterAttack(BYTE* buffer, int32 len);


private:
	std::map<EPacket_C2P_Protocol, std::function<void(URecvPacketProsesor& ,BYTE*, int32)>> Handler;

private:
	TQueue<RecvPacket> RecvQueue;
	FCriticalSection CriticalSession;

private:
	class UAYGameInstance* GameInstance;
};



