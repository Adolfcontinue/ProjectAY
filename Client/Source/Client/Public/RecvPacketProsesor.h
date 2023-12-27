// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AYTickObject.h"
#include <functional>
#include "RecvPacketProsesor.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FDEL_P2C_RESULT);

struct RecvPacket
{
	RecvPacket(BYTE* buffer, int32 len) : Buffer(buffer), Len(len) {}
	BYTE* Buffer;
	int32 Len;
};


UCLASS()
class CLIENT_API URecvPacketProsesor : public UAYTickObject
{
	GENERATED_BODY()

public:
	FDEL_P2C_RESULT Delegate_P2C_Result;

public:
	void Init();
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	UWorld* GetWorld() const override;
	
public:
	void Push(RecvPacket packet);
	void Push(BYTE* buffer, int32 len);

private:
	void PacketHandle(BYTE* buffer, int32 len);
	void Result_P2C_ResultLogin(BYTE* buffer, int32 len);

private:
	std::map<EPacket_C2P_Protocol, std::function<void(URecvPacketProsesor& ,BYTE*, int32)>> Handler;

private:
	std::queue<RecvPacket> RecvQueue;
};



