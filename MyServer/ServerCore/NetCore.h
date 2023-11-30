#pragma once

class NetObject : public enable_shared_from_this<NetObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class NetEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

class NetCore
{
public:
	NetCore();
	~NetCore();

	HANDLE		GetHandle() { return _iocpHandle; }

	bool		Register(NetObjectRef iocpObject);
	bool		Dispatch(uint32 timeoutMs = INFINITE);

private:
	HANDLE		_iocpHandle;
};