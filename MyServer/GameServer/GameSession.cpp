#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "World.h"

void GameSession::OnConnected()
{
    this->SetSessionKey(GGameSessionManager.IssueSessionKey());
    GGameSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
    GGameSessionManager.Add(this->GetSessionKey(), static_pointer_cast<GameSession>(shared_from_this()));
    std::cout << "Connect Client" << std::endl;
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
    std::cout << "DisConnected Client" << std::endl;
    GWorld->DoASync(&World::LeaveUser, GetSessionKey());
}
