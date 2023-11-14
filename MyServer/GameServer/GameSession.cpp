#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"

void GameSession::OnConnected()
{
    this->SetSessionKey(GGameSessionManager.FindSessionKey());
    GGameSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
    GGameSessionManager.Add(this->GetSessionKey(), static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
    PacketSessionRef session = GetPacketSessionRef();
    ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{
}

void GameSession::OnDisconnected()
{
    GGameSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));
    GGameSessionManager.Remove(this->GetSessionKey());
}
