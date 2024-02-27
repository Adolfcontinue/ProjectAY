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
	m_TransForm = MakeShared<TransFormAgent>(static_pointer_cast<Monster>(shared_from_this()));
	m_TransForm->Init(x, y, z, yaw);
	m_AI = MakeShared<AIAgent>(static_pointer_cast<Monster>(shared_from_this()));
	SetMonsterAbils();
}

void Monster::SetMonsterAbils()
{
	MaxHealth = 100;
	Health = MaxHealth;
	Power = 10;
}

void Monster::TakeDamage(uint64 attacker, float damageAmount)
{
	m_AI->SetTarget(attacker);
	Health -= damageAmount;
	if (Health <= 0)
		m_AI->SetState(Protocol::ActorState::DEAD);

	Protocol::P2C_ReportPlayerAttack sendPacket;
	sendPacket.set_attacker(attacker);
	sendPacket.set_victimkey(this->GetActorKey());
	sendPacket.set_damageamount(damageAmount);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	GWorld->BroadCast(sendBuffer);
}

void Monster::Update()
{
	if (!IsEnable())
		return;

	m_AI->Update();
	m_TransForm->Update();

	if (m_AI->GetState() != Protocol::ActorState::IDlE)
	{
		Protocol::P2C_ReportMonsterState sendPacket;
		sendPacket.set_actorkey(GetActorKey());
		Protocol::MonsterData* monsterData = sendPacket.mutable_monster();
		Protocol::TransFormData* transformData = monsterData->mutable_transform();
		Protocol::TransFormData* target = sendPacket.mutable_target();

		Protocol::TransFormData* monsterTransform = GetTransFormAgent()->GetTransForm();
		transformData->CopyFrom(*monsterTransform);
		monsterData->set_state(m_AI->GetState());
		target->set_x(m_AI->GetTargerPosition().X);
		target->set_y(m_AI->GetTargerPosition().Y);
		target->set_z(m_AI->GetTargerPosition().Z);
		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
		GWorld->BroadCast(sendBuffer);
	}
}




