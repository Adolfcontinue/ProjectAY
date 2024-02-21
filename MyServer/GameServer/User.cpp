#include "pch.h"
#include "User.h"
#include "Monster.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "ProtobufHelper.h"
#include "World.h"
#include "Struct.pb.h"
#include "Protocol.pb.h"


User::User()
{
	SetType(eActorType::User);
}

User::User(string id, string pw, int64 sessionKey, int32 level, int32 exp) 
	: _Id(id), _Pw(pw), _SessionKey(sessionKey), _Level(level), _Exp(exp)
{

}

void User::Init(int64 sessionKey, string id, string pw, float x, float y, float z, float yaw, int64 level, int64 exp, float dmg, float maxhp)
{
	SetID(id);
	SetPW(pw);
	SetSessionKey(sessionKey);
	TransForm = MakeShared<TransFormAgent>(static_pointer_cast<User>(shared_from_this()));
	Status = MakeShared<StatusAgent>(static_pointer_cast<User>(shared_from_this()));

	Status->Init(level, exp, dmg, maxhp);
	TransForm->Init(x, y, z, yaw);
}

void User::ReqWorldData()
{
	Protocol::P2C_ResultWorldData sendPacket;

	for (auto iter : GWorld->_Users)
	{
		if (iter.first == this->GetSessionKey())
			continue;

		UserRef itVal = iter.second;
		Protocol::UserData* user = sendPacket.add_users();
		Protocol::TransFormData* transform = user->mutable_transform();
		Protocol::TransFormData* itTransForm = itVal->GetTransFormAgent()->GetTransForm();
		transform->CopyFrom(*itTransForm);
		user->set_sessionkey(itVal->GetSessionKey());
		user->set_userkey(itVal->GetSessionKey());
	}

	for (auto iter : GWorld->_Monsters)
	{
		MonsterRef itVal = iter.second;
		Protocol::MonsterData* monster = sendPacket.add_monsters();
		Protocol::TransFormData* transform = monster->mutable_transform();
		Protocol::TransFormData* itTransForm = itVal->GetTransFormAgent()->GetTransForm();
		transform->CopyFrom(*itTransForm);
		monster->set_actorkey(itVal->GetActorKey());
		monster->set_type(Protocol::BEHOLDER);
	}

	GameSessionRef session = GGameSessionManager.Find(GetSessionKey());
	if (session == nullptr)
		return;

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
}

std::shared_ptr<StatusAgent> User::GetStatus()
{
	return Status;
}
