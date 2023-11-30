// Fill out your copyright notice in the Description page of Project Settings.


#include "NetWork/NetCore.h"
#include "NetWork/NetEvent.h"

NetCore::NetCore()
{
	_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (_iocpHandle != INVALID_HANDLE_VALUE)
		return;
}

NetCore::~NetCore()
{
	::CloseHandle(_iocpHandle);
}

bool NetCore::Register(NetObjectRef iocpObject)
{
	if (CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHandle, /*key*/0, 0) == NULL)
		return false;
	else
		return true;
}

bool NetCore::Dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	NetEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(_iocpHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs))
	{
		NetObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		int32 errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			// TODO : �α� ���
			NetObjectRef iocpObject = iocpEvent->owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
