// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameInstance.h"
#include "NetWork/NetSocketUtils.h"
#include "NetPacketHandler.h"
#include "PreLoder.h"
#include "Kismet/GameplayStatics.h"
#include "AYGameState.h"
#include "AYMonsterBase.h"
#include "MonsterBeholder.h"
#include "MonsterLizardMan.h"
#include "TableManager.h"

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
	TableManager = NewObject<UTableManager>();
	TableManager->TableLoad();
	auto a = TableManager->GetTableTest(3);
	int32 l = a->Level;
}

void UAYGameInstance::Shutdown()
{
	Socket->NetworkClose();
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

		state->RemovePlayer(userKey);
		it->Destroy();
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

void UAYGameInstance::RepPlayerAttack(int64 victimKey, double damageAmount)
{
	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
	{
		AAYMonsterBase* monster = state->FindMonster(victimKey);
		if (monster == nullptr)
			return;

		monster->TakeDamage(damageAmount);
		LOG("RepPlayerAttack");
	}
}

void UAYGameInstance::RepMonsterState(int64 actorKey, FVector pos, FQuat quat, Protocol::PlayerState state)
{
	AAYGameState* gameState = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(gameState))
	{
		auto it = gameState->FindMonster(actorKey);
		if (it == nullptr)
			return;

		it->RepMonsterState(pos, quat);
	}
}

void UAYGameInstance::AddMonster(Protocol::MonsterData monsterData)
{
	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
	{
		FVector location = FVector(monsterData.pos().x(), monsterData.pos().y(), 0);
		FRotator rotation = FRotator::ZeroRotator;

		AMonsterBeholder* newMonster = GetWorld()->SpawnActor<AMonsterBeholder>(AMonsterBeholder::StaticClass(), location, rotation);
		newMonster->SetActorKey(monsterData.actorkey());
		state->AddMonster(newMonster->GetActorKey(), newMonster);
	}
}




