#include "pch.h"
#include "Monster.h"
#include "World.h"
#include "ClientPacketHandler.h"
#include "ProtobufHelper.h"
#include "User.h"
#include "Define.h"
#include "Math.h"

Monster::Monster()
{
	SetType(eActorType::Monster);
}

Monster::~Monster()
{
	//shared_from_this();
}

void Monster::Init(int64 actorKey, eMonsterType monsterType, float x, float y, float z, float yaw)
{
	SetActorKey(actorKey);
	SetMonsterType(monsterType);
	SetActorState(Protocol::ActorState::IDlE);
	TransForm = MakeShared<TransFormAgent>(static_pointer_cast<Monster>(shared_from_this()));
	TransForm->Init(x, y, z, yaw);
	AI = MakeShared<AIAgent>(static_pointer_cast<Monster>(shared_from_this()));

}

void Monster::SetMonsterAbils()
{
	MaxHealth = 500;
	Health = MaxHealth;
	Power = 10;
}

void Monster::TakeDamage(uint64 attacker, float damageAmount)
{
	Health -= damageAmount;
	AI->DoASync(&AIAgent::SetTarget, attacker);

	Protocol::P2C_ReportPlayerAttack sendPacket;
	sendPacket.set_attacker(attacker);
	sendPacket.set_victimkey(this->GetActorKey());
	sendPacket.set_damageamount(damageAmount);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	GWorld->BroadCast(sendBuffer);
}

void Monster::Update()
{
	AI->Update();
	TransForm->Update();

	if (AI->GetState() != Protocol::ActorState::IDlE)
	{
		Protocol::P2C_ReportMonsterState sendPacket;
		sendPacket.set_actorkey(GetActorKey());
		Protocol::MonsterData* monsterData = sendPacket.mutable_monster();
		Protocol::TransFormData* transformData = monsterData->mutable_transform();
		Protocol::TransFormData* target = sendPacket.mutable_target();

		Protocol::TransFormData* monsterTransform = GetTransFormAgent()->GetTransForm();
		transformData->CopyFrom(*monsterTransform);
		monsterData->set_state(AI->GetState());
		target->set_x(AI->GetTargerPosition().X);
		target->set_y(AI->GetTargerPosition().Y);
		target->set_z(AI->GetTargerPosition().Z);
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
		GWorld->BroadCast(sendBuffer);
	}
}




