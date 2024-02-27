#include "pch.h"
#include "ThreadManager.h"
#include "NetService.h"
#include "NetSession.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include <tchar.h>
#include "Protocol.pb.h"
#include "DBConnectionPool.h"
#include "QueryRunManager.h"
#include "World.h"
#include "TableManager.h"

#include "TableData.h"
#include "MonsterTable.h"


#define _CRTDBG_MAP_ALLOC

enum
{
	WORKER_TICK = 64
};

void Process(ServerServiceRef& sevice)
{
	while (true)
	{
		LEndTickCount = GetTickCount64() + WORKER_TICK;

		sevice->GetCore()->Dispatch(10);

		ThreadManager::DistributeReserveJobs();
		ThreadManager::DoGlobalQueueWork();
	}
}

class Test
{
	int a = 0;
};

int main()
{
	std::cout << "Server Start .. !" << std::endl;

	GWorld->DoTimer(1000, &World::Update);

	ClientPacketHandler::Init();
	TableManager::Instance().Init();
	
	//MonsterTableData data = TABLE.GetTableData<MonsterTableData, MonsterTable>("MonsterTa1ble", 1001);

	//todo createmonster
	GWorld->Init();
	
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<NetCore>(),
		MakeShared<GameSession>,
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
			{
				while (true)
				{
					Process(service);
				}
			});
	}

	GThreadManager->Join();
	return 0;
}

