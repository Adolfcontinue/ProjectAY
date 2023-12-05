// Fill out your copyright notice in the Description page of Project Settings.


#include "NetWork/NetService.h"
#include "NetWork/NetSession.h"
#include "NetWork/Listener.h"

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
	lock_guard guard = lock_guard(_lock);
	_sessionCount++;
	_sessions.insert(session);
}

void NetService::ReleaseSession(NetSessionRef session)
{
	lock_guard guard = lock_guard(_lock);
	_sessions.erase(session);
	_sessionCount--;
}

ClientService::ClientService(NetAddress targetAddress, NetCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: NetService(ServiceType::Client, targetAddress, core, factory, maxSessionCount)
{
}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;

	const int32 sessionCount = GetMaxSessionCount();
	
	_clientSession = CreateSession();
	if (_clientSession->Connect() == false)
		return false;
	
	return true;
}






