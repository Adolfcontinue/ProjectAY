#include "pch.h"
#include "User.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "World.h"

User::User()
{

}

User::User(string id, string pw, int64 sessionKey, int32 level, int32 exp) 
	: _Id(id), _Pw(pw), _SessionKey(sessionKey), _Level(level), _Exp(exp)
{

}

void User::ReqWorldData()
{





	GameSessionRef session = GGameSessionManager.Find(GetSessionKey());
	if (session == nullptr)
		return;

	Protocol::P2C_ResultWorldData sendPacket;
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
}
