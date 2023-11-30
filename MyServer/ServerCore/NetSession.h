#pragma once
#include "NetCore.h"
#include "NetEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

class Service;

class NetSession : public NetObject
{
	friend class Listener;
	friend class NetCore;
	friend class NetService;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};

public:
	NetSession();
	virtual ~NetSession();

public:
	void				Send(SendBufferRef sendBuffer);
	bool				Connect();
	void				Disconnect(const WCHAR* cause);

	shared_ptr<NetService>	GetService() { return _service.lock(); }
	void				SetService(shared_ptr<NetService> service) { _service = service; }

public:
	void				SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress			GetAddress() { return _netAddress; }
	SOCKET				GetSocket() { return _socket; }
	bool				IsConnected() { return _connected; }
	NetSessionRef			GetSessionRef() { return static_pointer_cast<NetSession>(shared_from_this()); }

private:
	virtual HANDLE		GetHandle() override;
	virtual void		Dispatch(class NetEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
	bool				RegisterConnect();
	bool				RegisterDisconnect();
	void				RegisterRecv();
	void				RegisterSend();

	void				ProcessConnect();
	void				ProcessDisconnect();
	void				ProcessRecv(int32 numOfBytes);
	void				ProcessSend(int32 numOfBytes);

	void				HandleError(int32 errorCode);

protected:
	virtual void		OnConnected() { }
	virtual int32		OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void		OnSend(int32 len) { }
	virtual void		OnDisconnected() { }

public:
	int64 GetSessionKey() const;
	void SetSessionKey(int64 sessionKey);

protected:
	int64 _sessionKey;

private:
	weak_ptr<NetService>	_service;
	SOCKET				_socket = INVALID_SOCKET;
	NetAddress			_netAddress = {};
	Atomic<bool>		_connected = false;

private:
	USE_LOCK;
	RecvBuffer			_recvBuffer;
	Queue<SendBufferRef>	_sendQueue;
	Atomic<bool>		_sendRegistered = false;

private:
	ConnectEvent		_connectEvent;
	DisconnectEvent		_disconnectEvent;
	RecvEvent			_recvEvent;
	SendEvent			_sendEvent;
};

struct PacketHeader
{
	uint16 size;
	uint16 id; //protocol
};

class PacketSession : public NetSession
{
public:
	PacketSession();
	virtual ~PacketSession();

	PacketSessionRef GetPacketSessionRef() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) abstract;
};

