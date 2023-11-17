﻿#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include <tchar.h>
#include "Protocol.pb.h"
#include "DBConnectionPool.h"
#include "QueryRunManager.h"

void Process(ServerServiceRef& sevice)
{
	while (true)
	{
		sevice->GetIocpCore()->Dispatch();
		std::cout << "cll" << std::endl;
		QueryRunManager::Instance().Run();
		QueryRunManager::Instance().Complete();
	}
}

int main()
{
	std::cout << "Server Start .. !" << std::endl;

	ClientPacketHandler::Init();
	DBConnectionPool::Instance().Init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		ThreadManager::Instance().Launch([&service]()
			{
				while (true)
				{
					Process(service);
				}
			});
	}

	Process(service);

	ThreadManager::Instance().Join();

}

