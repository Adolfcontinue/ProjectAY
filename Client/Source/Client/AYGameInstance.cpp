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
	LOG_SCREEN(FColor::Red, "RecvPacketPush Success");
	LOG("RecvPacketPush Success");
}

void UAYGameInstance::AddPlayer(Protocol::UserData userData)
{
	LOG("AddPlayer");

	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
	{
		FVector location = FVector(userData.pos().x(), userData.pos().y(), userData.pos().z());
		FRotator rotation = FRotator(userData.rot().x(), userData.rot().y(), userData.rot().z());
		AOtherCharacter* newPlayer = GetWorld()->SpawnActor<AOtherCharacter>(AOtherCharacter::StaticClass(), location, rotation);
		newPlayer->SetPlayerKey(userData.userkey());
		state->AddPlayer(newPlayer->GetPalyerKey(), newPlayer);
	}
}

void UAYGameInstance::RemovePlayer(int64 userKey)
{
	LOG("RemovePlayer");

	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
	{
		state->FindPlayer(userKey)->Destroy();
		state->RemovePlayer(userKey);
	}
}




