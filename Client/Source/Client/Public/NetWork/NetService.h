// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
#include "NetAddress.h"
#include "NetCore.h"
#include "Listener.h"
#include <functional>

enum class ServiceType : uint8
{
	Server,
	Client
};

using SessionFactory = std::function<NetSessionRef(void)>;


class CLIENT_API NetService : public enable_shared_from_this<NetService>
{
public:
	NetService() {};
	NetService(ServiceType type, NetAddress address, NetCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~NetService();

	virtual bool Start() abstract;
	bool CanStart() { return _sessionFactory != nullptr; }

	virtual void CloseService();
	void SetSessionFactory(SessionFactory func) { _sessionFactory = func; }

	NetSessionRef CreateSession();
	void AddSession(NetSessionRef session);
	void ReleaseSession(NetSessionRef session);
	int32 GetCurrentSessionCount() { return _sessionCount; }
	int32 GetMaxSessionCount() { return _maxSessionCount; }

public:
	ServiceType	GetServiceType() { return _type; }
	NetAddress	GetNetAddress() { return _netAddress; }
	NetCoreRef& GetCore() { return _core; }
	void SetNetAddress(NetAddress address) { _netAddress = address; }

protected:
	mutex _lock;
	ServiceType			_type;
	NetAddress			_netAddress = {};
	NetCoreRef			_core;

	set<NetSessionRef>		_sessions;
	int32				_sessionCount = 0;
	int32				_maxSessionCount = 0;
	SessionFactory		_sessionFactory;
};

class CLIENT_API ClientService : public NetService
{
public:
	ClientService() {};
	ClientService(NetAddress targetAddress, NetCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ClientService() {}

	virtual bool	Start() override;

public:
	void SetMaxSessionCount(int32 cnt) { _maxSessionCount = cnt; }
	void SetCore(NetCoreRef core) { _core = core; }
};

