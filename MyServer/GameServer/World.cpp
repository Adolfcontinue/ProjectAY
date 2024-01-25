#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Monster.h"
#include "ProtobufHelper.h"
#include "ClientPacketHandler.h"
#include "ConsoleLogger.h"
#include "Actor.h"

shared_ptr<World> GWorld = make_shared<World>();

void World::EnterUser(UserRef user)
{
	user->SetActorKey(IssueActorKey());
	_Users[user->GetSessionKey()] = user;

	Protocol::P2C_ReportEnterUser packet;
	Protocol::UserData* data = packet.mutable_user();
	//Protocol::Float3* pos = data->mutable_position();
	ProtobufHelper::ConvertFloat3(data->mutable_position(), user->GetTransForm()->GetPosition());
	//Protocol::Float4* rot = data->mutable_rotation();
	ProtobufHelper::ConvertFloat4(data->mutable_rotation(), user->GetTransForm()->GetRotation());
	
	data->set_userkey(user->GetSessionKey());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	BroadCastExcept(sendBuffer, user->GetSessionKey());
}

void World::LeaveUser(int64 sessionKey)
{
	auto iter = _Users.find(sessionKey);
	if (iter == _Users.end())
		return;

	_Users.erase(sessionKey);

	Protocol::P2C_ReportLeaveUser packet;
	packet.set_userkey(sessionKey);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	BroadCastExcept(sendBuffer, sessionKey);
}

void World::BroadCast(SendBufferRef sendBuffer)
{
	for (auto& user : _Users)
	{
		GameSessionRef sessison = GGameSessionManager.Find(user.first);
		if (sessison != nullptr)
			sessison->Send(sendBuffer);
	}
}

void World::BroadCastExcept(SendBufferRef sendBuffer, int64 exceptKey)
{
	for (auto& user : _Users)
	{
		if (user.first == exceptKey)
			continue;

		GameSessionRef sessison = GGameSessionManager.Find(user.first);
		if (sessison != nullptr)
			sessison->Send(sendBuffer);
	}
}

UserRef World::FindUser(int64 key)
{
	auto iter = _Users.find(key);
	if (iter == _Users.end())
		return nullptr;

	return iter->second;
}

void World::MoveUser(int64 sessionKey, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 rot)
{
	UserRef user = FindUser(sessionKey);
	if (user == nullptr)
		return;

	user->GetTransForm()->SetPosition(pos);
	Protocol::P2C_ReportMove sendPacket;
	sendPacket.set_userkey(user->GetSessionKey());
	Protocol::PlayerState state;
	state = Protocol::PlayerState::MOVE;
	sendPacket.set_state(state);

	Protocol::PositionData* posData = sendPacket.mutable_posdata();
	Protocol::Float3* userPos = posData->mutable_posision();
	ProtobufHelper::ConvertFloat3(userPos, pos.x, pos.y, pos.z);
	Protocol::Float4* userRot = posData->mutable_rotation();
	ProtobufHelper::ConvertFloat4(userRot, rot.x, rot.y, rot.z, rot.w);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	BroadCastExcept(sendBuffer, sessionKey);
}

MonsterRef World::FindMonster(uint64 key)
{
	auto iter = _Monsters.find(key);
	if (iter == _Monsters.end())
		return nullptr;

	return iter->second;
}

//::todo create monster
void World::CreateMonster()
{
	MonsterRef newMonster = MakeShared<Monster>();
	newMonster->SetActorKey(IssueActorKey());
	newMonster->GetTransForm()->SetPosition(830.f, 1110.f, 90.f);
	newMonster->GetTransForm()->SetRotation(0.f, 0.f, 0.f, 1.f);
	newMonster->SetMonsterType(eMonsterType::Beholder);
	_Monsters.insert(pair<int64, MonsterRef>(newMonster->GetActorKey(), newMonster));
}

void World::Update()
{
	for (auto& it : _Monsters)
	{
		it.second->Update();
	}
}
