// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameInstance.h"
#include "NetWork/NetSocketUtils.h"
#include "NetPacketHandler.h"
#include "PreLoder.h"
#include "Kismet/GameplayStatics.h"
#include "AYGameState.h"


void UAYGameInstance::Init()
{
	Super::Init();

	NetSocketUtils::Init();
	Socket = new NetworkSocket();
	Socket->SetGameInstance(this);
	FRunnableThread::Create(Socket, TEXT("network_thread"));
	RecvProsesor = new URecvPacketProsesor();
	RecvProsesor->Init();
	RecvProsesor->SetGameInstance(this);
}

void UAYGameInstance::Shutdown()
{
	LOG("UAYGameInstance::Shutdown()");
	Socket->Stop();

	delete Socket;
	delete RecvProsesor;
}

NetworkSocket* UAYGameInstance::GetNetworkSocket()
{
	if (Socket == nullptr)
		return nullptr;

	return Socket;
}

URecvPacketProsesor* UAYGameInstance::GetRecvProsessor()
{
	return RecvProsesor;
}

void UAYGameInstance::RecvPacketPush(BYTE* buffer, int32 len)
{
	RecvProsesor->Push(buffer, len);
}

void UAYGameInstance::AddPlayer(Protocol::UserData userData)
{
	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
	{
		FVector location = FVector(userData.position().x(), userData.position().y(), userData.position().z());
		FRotator rotation = FRotator::ZeroRotator;
		AOtherCharacter* newPlayer = GetWorld()->SpawnActor<AOtherCharacter>(AOtherCharacter::StaticClass(), location, rotation);
		newPlayer->SetPlayerKey(userData.userkey());
		state->AddPlayer(newPlayer->GetPalyerKey(), newPlayer);
	}
}

void UAYGameInstance::RemovePlayer(int64 userKey)
{
	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
	{
		auto it = state->FindPlayer(userKey);
		if (it == nullptr)
			return;

		it->Destroy();
		state->RemovePlayer(userKey);
	}
}

void UAYGameInstance::RepPlayerMove(int64 userKey, FVector pos, FQuat quat, Protocol::PlayerState state)
{
	AAYGameState* gameState = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(gameState))
	{
		auto it = gameState->FindPlayer(userKey);
		if (it == nullptr)
			return;

		it->RepPlayerMove(pos, quat);
		it->SetAnimState(state);
	}
}




