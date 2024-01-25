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

void Monster::SetMonsterAbils()
{
	MaxHealth = 500;
	Health = MaxHealth;
	Power = 10;
}

void Monster::TakeDamage(uint64 attacker, float damageAmount)
{
	Health -= damageAmount;

	this->DoASync(&Monster::SetTarget, attacker);

	Protocol::P2C_ReportPlayerAttack sendPacket;
	sendPacket.set_attacker(attacker);
	sendPacket.set_victimkey(this->GetActorKey());
	sendPacket.set_damageamount(damageAmount);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	GWorld->BroadCast(sendBuffer);
}

void Monster::SetTarget(uint64 target)
{
	if (IsVaildTarget())
		return;

	TargetKey = target;

	UserRef targetUser = GWorld->FindUser(TargetKey);
	if (targetUser == nullptr)
		return;

	LookAt();
}

void Monster::Update()
{
	//::todo monster fsm
	//GWorld->BroadCast()
}

bool Monster::IsVaildTarget()
{
	if (TargetKey < 0)
		return false;

	UserRef target = GWorld->FindUser(TargetKey);
	if (target == nullptr)
	{
		TargetKey = -1;
		return false;
	}

	return true;
}

void Monster::LookAt()
{
	if (!IsVaildTarget())
		return;

	UserRef targetUser = GWorld->FindUser(TargetKey);
	if (targetUser == nullptr)
		return;

	DirectX::XMVECTOR pos = GetTransForm()->XMVECTORPosition();
	DirectX::XMVECTOR targetpos = targetUser->GetTransForm()->XMVECTORPosition();

	DirectX::XMVECTOR dir = DirectX::XMVectorSubtract(targetpos, pos);
	DirectX::XMVECTOR n_dir = DirectX::XMVector3Normalize(dir);

	DirectX::XMVECTOR forward = GetTransForm()->XMVECTORForwardVector();
	DirectX::XMVECTOR angle = DirectX::XMVector3AngleBetweenVectors(n_dir, forward);
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(AXIS_Z, DirectX::XMVectorGetX(angle));

	GetTransForm()->SetRotation(quat);
	
	Protocol::P2C_ReportMonsterState sendPacket;
	sendPacket.set_actorkey(GetActorKey());
	Protocol::PositionData* posData = sendPacket.mutable_posdata();
	Protocol::Float3* userPos = posData->mutable_posision();
	ProtobufHelper::ConvertFloat3(userPos, GetTransForm()->GetPosition());
	Protocol::Float4* userRot = posData->mutable_rotation();
	ProtobufHelper::ConvertFloat4(userRot, GetTransForm()->GetRotation());
	SendBufferRef sendBuffer1 = ClientPacketHandler::MakeSendBuffer(sendPacket);
	GWorld->BroadCast(sendBuffer1);
}




