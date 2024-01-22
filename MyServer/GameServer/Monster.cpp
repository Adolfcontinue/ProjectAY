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

void Monster::TakeDamage(uint64 attacker, double damageAmount)
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
	/*if (IsVaildTarget())
		return;*/

	TargetKey = target;

	UserRef targetUser = GWorld->FindUser(TargetKey);
	if (targetUser == nullptr)
		return;

	LookAt(targetUser->GetPosition());

	Protocol::P2C_ReportMonsterState sendPacket;
	sendPacket.set_actorkey(GetActorKey());
	Protocol::PositionData* posData = sendPacket.mutable_posdata();
	Protocol::Float3* userPos = posData->mutable_posision();
	ProtobufConverter::ConvertFloat3(userPos, GetPositionX(), GetPositionY(), GetPositionZ());
	Protocol::Float4* userRot = posData->mutable_rotation();
	ProtobufConverter::ConvertFloat4(userRot, GetRotationX(), GetRotationY(), GetRotationZ(), GetRotationW());
	SendBufferRef sendBuffer1 = ClientPacketHandler::MakeSendBuffer(sendPacket);
	GWorld->BroadCast(sendBuffer1);
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

void Monster::LookAt(Float3 targetpos)
{
	XMVECTOR position = Position.ConvertXMVECTOR();
	XMVECTOR targetPosition = targetpos.ConvertXMVECTOR();
	XMVECTOR direction = XMVector3Normalize(position - targetPosition);
	// 회전 축과 회전 각도를 계산
	float angle = atan2f(XMVectorGetX(direction), XMVectorGetZ(direction));

	XMVECTOR rotation = XMQuaternionRotationAxis(AXIS_Z, angle);

	Rotation.Set(
		XMVectorGetX(rotation),
		XMVectorGetY(rotation),
		XMVectorGetZ(rotation),
		XMVectorGetW(rotation)
	);
}


