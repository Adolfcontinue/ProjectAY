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

void User::ReqWorldData()
{
	Protocol::P2C_ResultWorldData sendPacket;

	for (auto iter : GWorld->_Users)
	{
		if (iter.first == this->GetSessionKey())
			continue;

		UserRef itval = iter.second;
		Protocol::UserData* user = sendPacket.add_users();
		
		Protocol::Float3* pos = user->mutable_position();
		ProtobufConverter::ConvertFloat3(pos, itval->GetPositionX(), itval->GetPositionY(), itval->GetPositionZ());
		
		Protocol::Float4* rot = user->mutable_rotation();
		ProtobufConverter::ConvertFloat4(rot, itval->GetRotationX(), itval->GetRotationY(), itval->GetRotationZ(), itval->GetRotationW());

		user->set_sessionkey(itval->GetSessionKey());
		user->set_userkey(itval->GetSessionKey());
	}

	for (auto iter : GWorld->_Monsters)
	{
		MonsterRef itval = iter.second;
		Protocol::MonsterData* monster = sendPacket.add_monsters();
		Protocol::Float3* pos = monster->mutable_pos();
		ProtobufConverter::ConvertFloat3(pos, itval->GetPositionX(), itval->GetPositionY(), itval->GetPositionY());
		monster->set_actorkey(itval->GetActorKey());
		monster->set_type(Protocol::BEHOLDER);
	}

	GameSessionRef session = GGameSessionManager.Find(GetSessionKey());
	if (session == nullptr)
		return;

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
}
