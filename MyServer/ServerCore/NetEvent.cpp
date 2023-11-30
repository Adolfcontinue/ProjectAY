#include "pch.h"
#include "NetEvent.h"


NetEvent::NetEvent(EventType type) : eventType(type)
{
	Init();
}

void NetEvent::Init()
{
	OVERLAPPED::hEvent = 0;
	OVERLAPPED::Internal = 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset = 0;
	OVERLAPPED::OffsetHigh = 0;
}
