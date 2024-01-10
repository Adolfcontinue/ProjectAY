#include "pch.h"
#include "User.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "ProtobufHelper.h"
#include "World.h"
#include "Struct.pb.h"
#include "Protocol.pb.h"


User::User()
{

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

		UserRef itVal = iter.second;
		Protocol::UserData* user = sendPacket.add_users();
		
		Protocol::Float3* pos = user->mutable_position();
		ProtobufConverter::ConvertFloat3(pos, itVal->GetPositionX(), itVal->GetPositionY(), itVal->GetPositionZ());
		
		Protocol::Float4* rot = user->mutable_rotation();
		ProtobufConverter::ConvertFloat4(rot, itVal->GetRotationX(), itVal->GetRotationY(), itVal->GetRotationZ(), itVal->GetRotationW());

		user->set_sessionkey(itVal->GetSessionKey());
		user->set_userkey(itVal->GetActorKey());
	}

	GameSessionRef session = GGameSessionManager.Find(GetSessionKey());
	if (session == nullptr)
		return;

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
}
