#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
#endif

#include "pch.h"
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
		ThreadManager::Instance().Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	ThreadManager::Instance().Join();

#ifdef  _DEBUG
	_CrtDumpMemoryLeaks();
#endif

}