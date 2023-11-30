#include "pch.h"
#include "NetService.h"
#include "NetSession.h"
#include "Listener.h"

/*-------------
	Service
--------------*/

NetService::NetService(ServiceType type, NetAddress address, NetCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: _type(type), _netAddress(address), _core(core), _sessionFactory(factory), _maxSessionCount(maxSessionCount)
{

}

NetService::~NetService()
{
}

void NetService::CloseService()
{
	// TODO
}

NetSessionRef NetService::CreateSession()
{
	NetSessionRef session = _sessionFactory();
	session->SetService(shared_from_this());

	if (_core->Register(session) == false)
		return nullptr;

	return session;
}

void NetService::AddSession(NetSessionRef session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void NetService::ReleaseSession(NetSessionRef session)
{
	WRITE_LOCK;
	ASSERT_CRASH(_sessions.erase(session) != 0);
	_sessionCount--;
}

/*-----------------
	ClientService
------------------*/

ClientService::ClientService(NetAddress targetAddress, NetCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: NetService(ServiceType::Client, targetAddress, core, factory, maxSessionCount)
{
}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;

	const int32 sessionCount = GetMaxSessionCount();
	for (int32 i = 0; i < sessionCount; i++)
	{
		NetSessionRef session = CreateSession();
		if (session->Connect() == false)
			return false;
	}

	return true;
}

ServerService::ServerService(NetAddress address, NetCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: NetService(ServiceType::Server, address, core, factory, maxSessionCount)
{
}

bool ServerService::Start()
{
	if (CanStart() == false)
		return false;

	_listener = MakeShared<Listener>();
	if (_listener == nullptr)
		return false;

	ServerServiceRef service = static_pointer_cast<ServerService>(shared_from_this());
	if (_listener->StartAccept(service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	// TODO

	NetService::CloseService();
}
