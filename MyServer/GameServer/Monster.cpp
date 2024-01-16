#include "pch.h"
#include "Monster.h"
#include "World.h"
#include "ClientPacketHandler.h"

Monster::Monster()
{
	SetType(eActorType::Monster);
}

Monster::~Monster()
{
	//shared_from_this();
}

void Monster::SetMonsterAbils()
{
	MaxHealth = 500;
	Health = MaxHealth;
	Power = 10;
}

void Monster::TakeDamage(uint64 attacker, double damageAmount)
{
	Health -= damageAmount;

	Protocol::P2C_ReportPlayerAttack sendPacket;
	sendPacket.set_attacker(attacker);
	sendPacket.set_victimkey(this->GetActorKey());
	sendPacket.set_damageamount(damageAmount);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	GWorld->BroadCast(sendBuffer);
}

void Monster::Update()
{
	//::todo monster fsm
	//GWorld->BroadCast()
}
