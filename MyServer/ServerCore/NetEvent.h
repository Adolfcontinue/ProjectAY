#pragma once

class NetSession;

enum class EventType : uint8
{
	Connect,
	Disconnect,
	Accept,
	Recv,
	Send
};

class NetEvent : public OVERLAPPED
{
public:
	NetEvent(EventType type);

	void			Init();

public:
	EventType		eventType;
	NetObjectRef	owner;
};

class ConnectEvent : public NetEvent
{
public:
	ConnectEvent() : NetEvent(EventType::Connect) { }
};

class DisconnectEvent : public NetEvent
{
public:
	DisconnectEvent() : NetEvent(EventType::Disconnect) { }
};

class AcceptEvent : public NetEvent
{
public:
	AcceptEvent() : NetEvent(EventType::Accept) { }

public:
	NetSessionRef	session = nullptr;
};

class RecvEvent : public NetEvent
{
public:
	RecvEvent() : NetEvent(EventType::Recv) { }
};

class SendEvent : public NetEvent
{
public:
	SendEvent() : NetEvent(EventType::Send) { }

	// TEMP
	Vector<SendBufferRef> sendBuffers;
};